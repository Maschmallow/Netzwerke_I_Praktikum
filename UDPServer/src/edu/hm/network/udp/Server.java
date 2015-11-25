package edu.hm.network.udp;

import java.net.SocketTimeoutException;

public class Server {
    private static final int PORT_NUMBER = 9876;
    public static void main(String[] args) throws Exception {
        int total_length = 0;
        UdpReceiver udpReceiver = new UdpReceiver(PORT_NUMBER);
        while(true)
        {   
           try {
                OwnUDPPacket udpPacket = 
                        udpReceiver.receive();
                total_length += udpPacket.getLength();
           } catch(SocketTimeoutException e) {
               // calculate the throughput
           }
        }
    }
}