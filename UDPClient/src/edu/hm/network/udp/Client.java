package edu.hm.network.udp;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.concurrent.TimeUnit;

public class Client {
	// every PACKETS a DELAY will be triggered.
	public static final int PACKETS = 2;
	// delay in milliseconds between every PACKETS.
	public static final int DELAY = 100;

	// duration of time in seconds in which packets are send.
	public static long MAX_TIME = 30;

	public static final int PACKET_SIZE = 1400;
	private static final int PORT_NUMBER = 9876;

	public static void main(String[] args) throws Exception {
		long startTime = 0;
		int packetsSend = 0;
		InetAddress IPAddress = InetAddress.getByName("127.0.0.1");
		DatagramSocket clientSocket = new DatagramSocket();

		while(true) {
			MyPacket udpPacket = new MyPacket(PACKET_SIZE);
			byte[] sendData = MyPacket.serializeUDPPacket(udpPacket);
			if (packetsSend%PACKETS == 0)
				Thread.sleep(DELAY);
			DatagramPacket sendPacket = 
					new DatagramPacket(sendData, sendData.length, IPAddress, PORT_NUMBER);
			clientSocket.send(sendPacket);
			
			//System.out.println("Send packet: " + udpPacket.getInstanceCounter());
			
			if (packetsSend == 0)
				startTime = System.nanoTime();
			else if(TimeUnit.NANOSECONDS.toSeconds(System.nanoTime()-startTime)>MAX_TIME)
				break;
			++packetsSend;
		}
		System.out.println("Packets send: " + packetsSend + " in " + MAX_TIME + " seconds.");
		System.out.println("Transmission rate: " + (packetsSend*PACKET_SIZE*8)/MAX_TIME + "kbit/s");
		clientSocket.close();
	}
}
