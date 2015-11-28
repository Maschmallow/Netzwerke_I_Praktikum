package edu.hm.network.udp;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.SocketException;
import java.net.SocketTimeoutException;

public class UdpReceiver {
	private DatagramSocket serverSocket;
	private byte[] receiveData;
	private boolean isVerbose = false;

	/**
	 * Creates a UdpReceiver listening on the specified port.
	 * 
	 * @param port - the udp receiver will listen on
	 * @param verbose - more debugging info
	 */
	public UdpReceiver(int port, boolean verbose) {
		try {
			// create a udp socket listing on the specified port
			serverSocket=new DatagramSocket(port);
			// all packets will be of size 1400 bytes
			serverSocket.setReceiveBufferSize(65536);
			//serverSocket.bind(new InetSocketAddress(InetAddress.getByName("192.168.178.28"), arg1));
			isVerbose = verbose;
			System.out.println("**** UDP server started ****");
			System.out.println("The server is listening on port: " + port);
			System.out.println("The server is waiting for client connections.");
		} catch(SocketException e) {
			System.err.println("Error: SocketException in UdpReceiver()");
				e.printStackTrace();
		}
	}
	/**
	 * 
	 * @param timeout - the time after which the blocking receive function
	 * returns.
	 * @throws SocketException 
	 */
	public void setTimoutTime(int timeout) throws SocketException {
		// time after which the blocking receive method
		// will be aborted
		serverSocket.setSoTimeout(timeout);
	}

	/**
	 * Closes the UDP receiver
	 */
	public void close()
	{
		serverSocket.close();
	}

	/**
	 * Receives one udp packet.
	 * 
	 * @return ownUdpPacket - returns the received udpPacket
	 */
	public MyPacket receive() throws IOException,SocketTimeoutException {
		receiveData = new byte[1400];
		DatagramPacket recvPacket = new DatagramPacket(receiveData, receiveData.length);
		
		/* receive UDP packets */
		serverSocket.receive(recvPacket);
		
		/* deserialize received byte array into OwnUDPPacket format */
		MyPacket udpPacket =
				MyPacket.deserializePacket(recvPacket.getData());
		udpPacket.setLength(recvPacket.getLength());
		// Sender info
		if (isVerbose) {
	      InetAddress address = recvPacket.getAddress();
	      int         port    = recvPacket.getPort();
	      int         len     = recvPacket.getLength();
	      System.out.printf( "Anfrage von %s vom Port %d mit der Länge %d. ID: %d%n",
	            address, port, len, udpPacket.getInstanceCounter());
		}

      return udpPacket;
	}
}
