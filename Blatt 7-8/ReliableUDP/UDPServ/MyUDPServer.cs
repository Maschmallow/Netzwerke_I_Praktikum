using System;
using System.Diagnostics;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Security.Cryptography;

namespace UDPServ
{
    public class MyUdpServer
    {
        public enum State
        {
            WaitForConnection,
            SendSynAck,
            ReceivePacket,
            SaveToFile
        }

        public static int ListenPort = 9003;
        public static int ReceivedFiles;
        private string _fileEnding;
        private const int PacketSizeBytes = 1440;
        private IPEndPoint _sender;
        private UdpClient _udpClient;
        private State _currentState = State.WaitForConnection;
        private byte[] _payloadBuffer;
        private int _acknowledgedBytes = 0;
        private static int NrPackets = 0;
        private bool _fileRecv = false;

        private Stopwatch _stopwatch;

        public MyUdpServer()
        {
            _fileEnding = "";
            ReceivedFiles = 0;
        }
        public void DisplayServerInformation()
        {
            Console.WriteLine("***** Zuverlässige Dateiübertragung: Server *****");
            Console.WriteLine("Version: 0.1");
        }
        public bool IsSyn(RPH rph)
        {
            return !IsCorrupt(rph) && rph._syn;
        }

        public bool FilterDgram(double bitcorruption, double packetloss, double duplicate, ref byte[] dgram)
        {
            return false;
            // Filter kein paket wenn größer 1.0
            if ((bitcorruption + packetloss + duplicate) > 1.0)
                return false;
            var rnd = new Random();
            var rndvalue = rnd.NextDouble();
            if (rndvalue < bitcorruption)
            {
                Console.WriteLine("Filter: corrupt packet");
                for (int i = 0; i < dgram.Length; i++)
                    dgram[i] = (byte)'#';
                return false;
            }
            else if (bitcorruption < rndvalue && rndvalue < (packetloss + bitcorruption))
            {
                // Paket überspringt Ack
                Console.WriteLine("Filter: Packet Lost");
                return true;
            }
            else if ((packetloss + bitcorruption) < rndvalue && rndvalue < (duplicate + packetloss + bitcorruption))
            {
                // dupliziere paket:
                // Ack das selbe Paket 2 mal
                Console.WriteLine("Filter: duplicate packet");
                AckPacket(dgram);
            }
            return false;
        }

        public bool Init()
        {
            _acknowledgedBytes = 0;
            _fileEnding = "";
            _fileRecv = false;
            NrPackets = 0;
            DisplayServerInformation();
            Console.WriteLine("Warte auf Verbindung von Clienten...");

            _sender = new IPEndPoint(IPAddress.Any, 0);
            IPEndPoint endAddress = new IPEndPoint(IPAddress.Any, ListenPort);
            try
            {
                if (_udpClient == null)
                _udpClient = new UdpClient(endAddress);

            
                byte[] dgram = _udpClient.Receive(ref _sender);
                RPH rph = RPH.Deserialize(dgram);

                if (IsCorrupt(rph))
                {
                    // send nak
                    return false;
                }
                else
                {
                    _currentState = State.SendSynAck;
                }

                _fileEnding = rph._fileEnding;
                _payloadBuffer = new byte[rph._fileSize];

                return true;
            }
            catch (SocketException e)
            {
                Console.WriteLine(e);
                return false;
            }
        }

        public void SetChecksum(ref byte[] packet)
        {
            RPH rph = RPH.Deserialize(packet);
            var md5 = MD5.Create();
            rph._checksum = BitConverter.ToInt32(md5.ComputeHash(packet), 0);
            byte[] newHead = rph.Serialize();
            Array.Copy(newHead, packet, newHead.Length);
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
        public bool IsCorrupt(byte[] packet)
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

        public void WriteToFile(byte[] buffer)
        {
            try
            {
                ReceivedFiles++;
                string filename = ReceivedFiles + _fileEnding;
                var fs = new FileStream(filename, FileMode.Create, FileAccess.Write);
                Console.WriteLine("Received one file.");
                Console.WriteLine("Saving file with name: " + filename);
                fs.Write(buffer, 0, buffer.Length);
                fs.Close();
                _currentState = State.WaitForConnection;
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
        }

        public void SendSynAck()
        {
            var rph = RPH.CreateSynAckPacket();
            var dgram = rph.Serialize();
            SetChecksum(ref dgram);
            _udpClient.Send(dgram, dgram.Length, _sender);
            _currentState = State.ReceivePacket;
        }

        public void AckPacket(byte[] buf)
        {

            // Deserialize our protocol
            var rph = RPH.Deserialize(buf);

            // Calculate the size of our protocol
            int headSize = rph.GetByteLength();

            // if received packet is a retransmission or corrupt or packet reordering took place
            if (IsCorrupt(buf) || _acknowledgedBytes != rph._seqNr)
            {
                // Send NAck
                Console.WriteLine("Packet was corrupt or it was a retransmission");
                var ack = RPH.CreateNAckPacket();
                var dgram = ack.Serialize();
                SetChecksum(ref dgram);
                _udpClient.Send(dgram, dgram.Length, _sender);
            }
            else if (!IsCorrupt(buf) && rph._seqNr == _acknowledgedBytes)
            {
                _acknowledgedBytes = rph._seqNr + buf.Length - headSize;
                // Copy received bytes into receive buffer
                Array.Copy(buf, headSize, _payloadBuffer, rph._seqNr, buf.Length - headSize);
                var ack = RPH.CreateAckPacket(_acknowledgedBytes, 0);
                var dgram = ack.Serialize();
                SetChecksum(ref dgram);
                _udpClient.Send(dgram, dgram.Length, _sender);

                if (_payloadBuffer.Length == _acknowledgedBytes)
                {
                    _currentState = State.SaveToFile;
                }
            }
            else
            {
                Console.WriteLine("Not defined");
            }
            NrPackets++;
//             Console.WriteLine(NrPackets + ".Paket");
//             Console.WriteLine("Sequenznummer: " + rph._seqNr);
//             Console.WriteLine("AckNr: " + _acknowledgedBytes);
        }

        public void ReceivePacket()
        {
            var buf = _udpClient.Receive(ref _sender);
            // Filter the dgram (Aufgabe: 7.1: e)
            if (!FilterDgram(0.05, 0.1, 0.05, ref buf))
            {
                AckPacket(buf);
            }
        }

        public void Exec()
        {
            while (!_fileRecv)
            {
                switch (_currentState)
                {
                    case State.WaitForConnection:
                        {
                            Init();
                            break;
                        }
                    case State.SendSynAck:
                        {
                            SendSynAck();
                            _stopwatch = Stopwatch.StartNew();
                            break;
                        }
                    case State.ReceivePacket:
                        {
                            ReceivePacket();
                            break;
                        }
                    case State.SaveToFile:
                        {
                            _stopwatch.Stop();
                            long milliSec = _stopwatch.ElapsedMilliseconds;

                            Console.WriteLine();
                            WriteToFile(_payloadBuffer);
                            Console.WriteLine("Übertragungsdauer: " + (double)milliSec/1000.0 + " Sekunden.\n");
                            break;
                        }
                }
            }
        }
    }
}