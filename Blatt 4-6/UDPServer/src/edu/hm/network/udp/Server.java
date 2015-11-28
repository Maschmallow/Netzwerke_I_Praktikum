package edu.hm.network.udp;

import java.io.IOException;
import java.net.SocketTimeoutException;
import java.util.concurrent.TimeUnit;

public class Server {
	private static final int PORT_NUMBER = 9876;
	private static final int TIMEOUT = 10000; // ms = 5s
	private static final boolean VERBOSE = false;

	private UdpReceiver udpReceiver;
	private TcpReceiver tcpReceiver;

	/* Contains the byte size of all received packets*/
	private long totalPacketSize = 0;

	/* Contains the number of received packets */
	private long receivedPackets = 0;

	/* use TCP or UDP */
	private boolean isTCP = false;

	/* time in nanoseconds the server received first packet */
	private long startTime = 0;

	/* time in nanoseconds the server received last packet */
	private long endTime = 0;

	private MyPacket prevUDPPacket = null;

	public Server(boolean isTCP) {
		this.isTCP = isTCP;

		if(isTCP)
			tcpReceiver = new TcpReceiver(PORT_NUMBER, VERBOSE);
		else
			udpReceiver = new UdpReceiver(PORT_NUMBER, VERBOSE);
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
		MyPacket myPacket = null;

		/*
		 * Receive UDP Packets
		 * First call is blocking rest has timeout
		 */
		if(isTCP)
			myPacket = tcpReceiver.receive();
		else
			myPacket = udpReceiver.receive();

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
			udpReceiver.setTimoutTime(TIMEOUT);
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

	}

	public static void main(String[] args) {
		Server server = new Server(false);

		server.start();
	}
}