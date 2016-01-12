using System;
using System.Diagnostics;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Security.Cryptography;

namespace ReliableUDP
{
    public class MyUDPClient
    {
        
        public enum State
        {
            SendPacket,
            WaitForAck,
            EstablishConnection,
            WaitForSynAck,
            CloseConnection,
            FatalError
        }

        // The port the server will listen to
        public const int ListenPort = 9003;

        // The Packet Size 
        public const int PacketSizeBytes = 1460;

        // timeout in ms
        public const int Timeout = 1000;

        // the maximum retransmission tries of one packet
        // before the connection will be closed
        public const int MaxRetransTries = 100;

        public const int MaxConTries = 100;
        private byte[] _filechunk;
        // The current state of our client
        private State _currentState = State.EstablishConnection;
        
        // our socket to send packets from
        private Socket _sendingSocket;

        // the receiver (our server end point)
        private IPEndPoint _endPoint;

        // the data read in from a file
        private byte[] _fileData;

        // has the file already been send
        private bool _fileSend = false;

        // the retransmission tries of one packet
        public int _tries = 0;

        // acknowledged bytes
        private int _localSeqNr = 0;

        private string _filename;
        private string _hostname;

        public MyUDPClient(string filename, string hostname)
        {
            _filename = filename;
            _hostname = hostname;
        }

        public void SendSyn(int filelength, string fileEnding)
        {
            // Establish the connection
            RPH syn = RPH.CreateSynPacket(filelength, fileEnding);
            byte[] dgram = syn.Serialize();
            SetChecksum(ref dgram);
            try
            {
                _sendingSocket?.SendTo(dgram, _endPoint);
            }
            catch (SocketException e)
            { 
                Console.WriteLine(e.ToString());
                _tries++;
                if (_tries > MaxConTries)
                {
                    return;
                }
                SendSyn(filelength, fileEnding);
                _tries = 0;
            }
        }

        public bool IsCorrupt(RPH rph)
        {
            int checksum = rph._checksum;
            rph._checksum = 0;
            byte[] packet = rph.Serialize();
            var md5 = MD5.Create();
            int calcChecksum = BitConverter.ToInt32(md5.ComputeHash(packet), 0);
            return checksum != calcChecksum;
        }

        public void WaitForSynAck()
        {
            EndPoint sender = (EndPoint)_endPoint;
            var ackn = new byte[RPH.GetPacketByteLength()];
            // set the timeout for receiving acks (retransmission timeout)
            _sendingSocket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReceiveTimeout, Timeout);
            try
            {
                _sendingSocket.ReceiveFrom(ackn, ref sender);

                var rph = RPH.Deserialize(ackn);
                if (IsCorrupt(rph) || !IsSynAck(rph))
                {
                    _currentState = State.EstablishConnection;
                    return;
                }
                else
                {
                    Console.WriteLine("Connection Established");
                    _currentState = State.SendPacket;
                }
            }
            catch (SocketException e)
            {
                if (e.SocketErrorCode == SocketError.TimedOut)
                {
                    Console.WriteLine(e.ToString());
                    Console.WriteLine("No Connection could be established");
                }
                _currentState = State.EstablishConnection;
            }
        }

        public bool Init()
        { 
            // Initializes the end point to our server application
            _endPoint = new IPEndPoint(IPAddress.Parse(_hostname), ListenPort);

            // Initialize the socket
            if (_sendingSocket == null)
                _sendingSocket = new Socket(
                    AddressFamily.InterNetwork, 
                    SocketType.Dgram, 
                    ProtocolType.Udp);

            try
            {
                // Read in file data
                _fileData = File.ReadAllBytes(_filename);

                string fileEnding = "";
                var index = _filename.LastIndexOf(".");

                if (index != -1)
                    fileEnding = _filename.Substring(index);

                // Send the syn packet for connection establishment
                SendSyn(_fileData.Length, fileEnding);

                // now wait for ack for that syn
                _currentState = State.WaitForSynAck;
            }
            catch (FileNotFoundException e)
            {
                Console.Error.WriteLine("File not found! " + e.ToString());
                return false;
            }
            catch (Exception e)
            {
                Console.Error.WriteLine(e.ToString());
                return false;
            }

            return true;
        }

        public byte[] FileToChunk(byte[] filedata, int index, int chunkSize)
        {
            var buf = new byte[chunkSize];

            Array.Copy(_fileData, index, buf, 0, chunkSize);

            return buf;
        }

        public void SetChecksum(ref byte[] packet)
        {
            RPH rph = RPH.Deserialize(packet);
            var md5 = MD5.Create();
            rph._checksum = BitConverter.ToInt32(md5.ComputeHash(packet), 0);
            byte[] newHead = rph.Serialize();
            Array.Copy(newHead, packet, newHead.Length);
        }

        public bool IsLastPacket(int payloadSize)
        {
            return (_fileData.Length - _localSeqNr) < payloadSize;
        }

        private void SendOnePacket()
        {       
            int headSize = RPH.GetPacketByteLength();

            byte[] packetBuf = null;

            if (!IsLastPacket(PacketSizeBytes-headSize))
            {
                _filechunk = FileToChunk(_fileData, _localSeqNr, PacketSizeBytes-headSize); 
                packetBuf = new byte[PacketSizeBytes];
            }
            else
            {
                _filechunk = FileToChunk(_fileData, _localSeqNr, _fileData.Length - _localSeqNr);
                packetBuf = new byte[_filechunk.Length + headSize];
                _fileSend = true;
            }

            var rph = RPH.CreatePacketHeader(_localSeqNr, 0);

            byte[] header = rph.Serialize();

            // Copy together one packet: header with payload
            Array.Copy(header, packetBuf, headSize);
            Array.Copy(_filechunk, 0, packetBuf, headSize, _filechunk.Length);

            // Last set the Checksum of the packet
            SetChecksum(ref packetBuf);

            // Now Send the packet
            _sendingSocket.SendTo(packetBuf, _endPoint);

            Console.WriteLine("Paket versendet");

            // Change State
            _currentState = State.WaitForAck;
        }

        private void WaitForAck()
        {
            EndPoint sender = (EndPoint)_endPoint;
            var ackn = new byte[RPH.GetPacketByteLength()];
            _tries++;

            if (MaxRetransTries < _tries)
            {
                _currentState = State.FatalError;
                return;
            }

            try
            {
                _sendingSocket.ReceiveFrom(ackn, ref sender);

                var rph = RPH.Deserialize(ackn);

                // Ack is corrupt
                if (IsCorrupt(rph, ackn) || !IsAck(rph))
                {
                    // If Ack is corrupt resend Packet
                    Console.WriteLine("Corrupt or NAck: Resend Packet");
                }           
                else if (IsAck(rph) && !IsCorrupt(rph) && rph._ackNr != _localSeqNr)
                {
                    _tries = 0;
                    Debug.Assert(rph != null, "rph != null");
                    _localSeqNr += _filechunk.Length;
                    _currentState = State.SendPacket;
                }
                else
                {
                    Console.WriteLine("Not defined");
                }
            }
            catch (SocketException e)
            {
                if (e.SocketErrorCode == SocketError.TimedOut)
                {
                    // Timeout: Resend Packet
                    Console.WriteLine("Timeout: Resend Packet");
                    SendOnePacket();
                }
                else
                {
                    Console.WriteLine("Fatal Error");
                    _currentState = State.FatalError;
                    return;
                }
            }
        }

        public bool IsSynAck(RPH rph)
        {
            return rph._ack && rph._syn && rph._ackNr == 1;
        }
        public bool IsAck(RPH rph)
        {
            return  rph._ack && !rph._syn;
        }

        public bool IsCorrupt(RPH rph, byte[] packet)
        {
            var copyPacket = new byte[packet.Length];
            Array.Copy(packet, copyPacket, packet.Length);
            var recvRph = RPH.Deserialize(packet);
            int recvChecksum = recvRph._checksum;
            recvRph._checksum = 0;
            byte[] newHead = recvRph.Serialize();
            Array.Copy(newHead, copyPacket, newHead.Length);
            var md5 = MD5.Create();
            int calcChecksum = BitConverter.ToInt32(md5.ComputeHash(copyPacket), 0);

            return calcChecksum != recvChecksum;
        }

        public void Exec()
        {
            while (!_fileSend)
            {
                switch (_currentState)
                {
                    case State.EstablishConnection:
                    {
                        Init();
                        break;
                    }
                    case State.SendPacket:
                    {
                        SendOnePacket();
                        break;
                    }
                    case State.WaitForAck:
                    {
                        WaitForAck();
                        break;
                    }
                    case State.WaitForSynAck:
                    {
                        WaitForSynAck();
                        break;
                    }
                    case State.CloseConnection:
                    {
                        break;
                    }
                }
            }
        }
    }
}