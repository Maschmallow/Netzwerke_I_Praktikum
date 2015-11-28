package edu.hm.network.udp;

import java.net.InetAddress;
import java.util.concurrent.TimeUnit;

public class Client {
	// every PACKETS a DELAY will be triggered.
	public static final int PACKETS = 10;
	// delay in milliseconds between every PACKETS.
	public static final int DELAY = 200;

	// duration of time in seconds in which packets are send.
	public static final long MAX_TIME = 30;
	
	// Host with port number to which connection is established
	public static final String HOST = "192.168.178.56";
	private static final int PORT_NUMBER = 9876;

	// the size of the packet (goodput)
	public static final int PACKET_SIZE = 1400;
	
	public static final boolean ISTCP = true;
	public static final boolean VERBOSE = false;
	
	
	
	private Sender sender;
	
	public void start() throws Exception {
		long startTime = 0;
		int packetsSend = 0;
		
		InetAddress IPAddress = InetAddress.getByName(HOST);
		
		if (ISTCP)
			sender = new TCPSender();
		else
			sender = new UDPSender();
		
		if (sender == null)
			return;
		
		sender.initalize(IPAddress, PORT_NUMBER);
		
		while(true) {
			if (packetsSend%PACKETS == 0)
				Thread.sleep(DELAY);
			
			MyPacket myPacket = new MyPacket(PACKET_SIZE);
			byte[] sendData = MyPacket.serializeUDPPacket(myPacket);
			
			sender.send(sendData);
			
			if (VERBOSE)
				System.out.println("Send packet: " + myPacket.getInstanceCounter());
			
			/* Start timer if first packet was send */
			if (packetsSend == 0)
				startTime = System.nanoTime();
			/* Check if MAX_TIME was passed */
			else if(TimeUnit.NANOSECONDS.toSeconds(System.nanoTime()-startTime)>MAX_TIME)
				break;
			++packetsSend;
		}
		sender.close();
		
		System.out.println("Packets send: " + packetsSend + " in " + MAX_TIME + " seconds.");
		/* Calculate transmission rate */
		System.out.println("Transmission rate: " + (packetsSend*PACKET_SIZE*8)/MAX_TIME + "kbit/s");
	}


	public static void main(String[] args) {
		Client client = new Client();
		try {
			client.start();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
