package edu.hm.network.udp;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.net.SocketTimeoutException;

public class UdpReceiver {
	private DatagramSocket serverSocket;
	private byte[] receiveData;
	
	// the timeout after which the blocking receive method 
	// will be aborted
	private final int timeout = 200;
	
	/**
	 * Creates a UdpReceiver listening on the specified port.
	 * 
	 * @param port - the udp receiver will listen on
	 */
	public UdpReceiver(int port) {
		try {
			// create a udp socket listing on the specified port
			serverSocket=new DatagramSocket(port);
			// all packets will be of size 1400 bytes
			serverSocket.setReceiveBufferSize(1400);
			// time after which the blocking receive method
			// will be aborted
			serverSocket.setSoTimeout(timeout);
		} catch(SocketException e) {
			System.err.println("Error: SocketException in UdpReceiver()");
		}
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
	public OwnUDPPacket receive() throws SocketTimeoutException {
		DatagramPacket recvPacket = new DatagramPacket(receiveData, receiveData.length);
		try {
            serverSocket.receive(recvPacket);
            OwnUDPPacket udpPacket =
                    OwnUDPPacket.deserializeUDPPacket(recvPacket.getData());
            return udpPacket;
        }
		catch (IOException e) {
            e.printStackTrace();
        }
		return null;
	}
}
