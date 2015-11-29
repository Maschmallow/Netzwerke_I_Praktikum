package edu.hm.network.udp;

import java.io.IOException;
import java.net.SocketTimeoutException;
import java.util.concurrent.TimeUnit;

public class Server {
	private static final int PORT_NUMBER = 9876;
	private static final int TIMEOUT = 10000; // ms = 5s
	private static final boolean VERBOSE = false;

	/* Contains the byte size of all received packets*/
	private long totalPacketSize = 0;

	/* Contains the number of received packets */
	private long receivedPackets = 0;

	/* use TCP or UDP */
	private boolean isTCP = true;

	/* time in nanoseconds the server received first packet */
	private long startTime = 0;

	/* time in nanoseconds the server received last packet */
	private long endTime = 0;

	private MyPacket prevUDPPacket = null;
	
	private Receiver receiver = null;

	public Server(boolean isTCP) {
		this.isTCP = isTCP;

		if(isTCP) {
			receiver = new TcpReceiver(PORT_NUMBER, VERBOSE);
		}
		else
			receiver = new UdpReceiver(PORT_NUMBER, VERBOSE);
	}

	/**
	 * Convert bytes to kilobytes
	 * @param bytes
	 * @return kilobytes
	 */
	private long convertToKBits(long bytes) {
		return (bytes * 8) / 1024;
	}

	private long calcGoodput() {
		return convertToKBits(totalPacketSize) / TimeUnit.NANOSECONDS.toSeconds(endTime-startTime);
	}

	boolean isPacketLost(MyPacket lastPacket) {
		return (prevUDPPacket != null && lastPacket != null 
				&& prevUDPPacket.getInstanceCounter() != lastPacket.getInstanceCounter()-1);
	}

	/**
	 * 
	 * @param lastPacket the last packet received
	 * @return the number of packets lost
	 */
	private long numPacketsLost(MyPacket lastPacket) {
		return lastPacket.getInstanceCounter() - prevUDPPacket.getInstanceCounter();
	}

	public void receivePackets() throws IOException,SocketTimeoutException {
		if (receiver == null)
			return;
			
		/*
		 * Receive UDP Packets
		 * First call is blocking rest has timeout
		 */
		MyPacket myPacket = receiver.receive();

		if(myPacket == null) {
			return;
		} else {
			/* sum up length of all received packets */
			totalPacketSize += myPacket.getLength(); 
		}

		/*
		 * If first packet received start Timer and
		 * set the timeout time
		 */
		if(receivedPackets == 0) {
			startTime = System.nanoTime();
			if (!isTCP)
			    receiver.setTimeoutTime(TIMEOUT);
			System.out.println("Erstes Paket empfangen...");
		}

		// Set end time after each received packet
		// it could be the last
		endTime = System.nanoTime();
		
		receivedPackets++;

		/*
		 * Recognize lost packets.
		 */
		if (isPacketLost(myPacket))
			System.out.println("Packets lost: " + numPacketsLost(myPacket));

		/*
		 * save previous received Packet to recognize packet loss
		 */
		prevUDPPacket = myPacket;
	}


	void start() {
		while(true)
		{
			try {
				receivePackets();
			} catch(SocketTimeoutException e) {
				System.out.println("Der Goodput beträgt: " + calcGoodput() + " kbit/s");
				break;
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		
		receiver.close();
	}

	public static void main(String[] args) {
		Server server = new Server(true);

		server.start();
	}
}