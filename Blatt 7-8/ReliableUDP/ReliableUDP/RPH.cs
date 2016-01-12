using System.IO;
using System.Net;

namespace ReliableUDP
{
    // Reliable protocol header
    public class RPH
    {
        public int _checksum { get; set; }
        public int _seqNr { get; set; }
        public int _ackNr { get; set; }
        public int _fileSize { get; set; }
        public string _fileEnding { get; set; }
        public bool _syn { get; set; }
        public bool _ack { get; set; }

        public RPH()
        {
            _fileEnding = "";
        }

        public int GetByteLength()
        {
            return Serialize().Length;
        }

        public static int GetPacketByteLength()
        {
            RPH rph = new RPH();
            return rph.GetByteLength();
        }

        public static RPH CreateSynPacket(int fileSize, string fileEnding)
        {
            RPH rph = new RPH
            {
                _seqNr = 0,
                _ackNr = 0,
                _fileSize = fileSize,
                _syn = true,
                _ack = false,
                _fileEnding = fileEnding
            };

            return rph;
        }

        public static RPH CreateSynAckPacket()
        {
            RPH rph = new RPH
            {
                _seqNr = 0,
                _ackNr = 1,
                _fileSize = 0,
                _syn = true,
                _ack = true
            };

            return rph;
        }

        public static RPH CreatePacketHeader(int seqNr, int ackNr)
        {
            RPH rph = new RPH
            {
                _seqNr = seqNr,
                _ackNr = ackNr,
                _syn = false,
                _fileSize = 0,
                _ack = true
            };

            return rph;
        }

        public byte[] Serialize()
        {
            using (var m = new MemoryStream())
            {
                using (var writer = new BinaryWriter(m))
                {
                    writer.Write(_checksum);
                    writer.Write(_seqNr);
                    writer.Write(_ackNr);
                    writer.Write(_fileSize);
                    writer.Write(_fileEnding);
                    writer.Write(_syn);
                    writer.Write(_ack);
                }
                return m.ToArray();
            }
        }

        static public RPH Deserialize(byte[] header)
        {
            var myPacket = new RPH();
            using (var m = new MemoryStream(header))
            {
                using (var reader = new BinaryReader(m))
                {
                    myPacket._checksum = reader.ReadInt32();
                    myPacket._seqNr = reader.ReadInt32();
                    myPacket._ackNr = reader.ReadInt32();
                    myPacket._fileSize = reader.ReadInt32();
                    myPacket._fileEnding = reader.ReadString();
                    myPacket._syn = reader.ReadBoolean();
                    myPacket._ack = reader.ReadBoolean();
                }
                return myPacket;
            }
        }
    }
}
