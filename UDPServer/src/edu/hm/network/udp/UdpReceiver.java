package edu.hm.network.udp;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;

public class UdpReceiver {
	private DatagramSocket serverSocket;
	private byte[] receiveData;
	
	// the timeout after which the blocking receive method 
	// will be aborted
	private final int timeout = 200;
	
	public UdpReceiver(int port) {
		try {
			// create a udp socket
			serverSocket=new DatagramSocket(port);
			// all packets will be of size 1400 bytes
			serverSocket.setReceiveBufferSize(1400);
			serverSocket.setSoTimeout(timeout);
		} catch(SocketException e) {
			System.err.println("Error: SocketException in UdpReceiver()");
		}
	}
	
	public void close()
	{
		serverSocket.close();
	}
	
	public OwnUDPPacket receive() {
		int receivedBytes = 0;
		DatagramPacket recvPacket = new DatagramPacket(receiveData, receiveData.length);
		try {
			receivedBytes = serverSocket.receive(recvPacket);
		}
	}
}
