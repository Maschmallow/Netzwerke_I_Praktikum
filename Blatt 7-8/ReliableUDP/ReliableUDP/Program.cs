using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace ReliableUDP
{
    class Program
    {
        private 
        static void Main(string[] args)
        {
            if (args.Length < 2)
            {
                Console.WriteLine("Usage: [filename] [target ip4 addr]");
                return;
            }

            var myUdpClient = new MyUDPClient(args[0], args[1]);
            myUdpClient.Exec();
        }
    }
}
