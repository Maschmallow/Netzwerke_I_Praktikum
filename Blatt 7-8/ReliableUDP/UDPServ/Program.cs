using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace UDPServ
{
    class Program
    {
        static void Main(string[] args)
        {
            MyUdpServer myUdpServer = new MyUdpServer();
            myUdpServer.Exec();
        }
    }
}
