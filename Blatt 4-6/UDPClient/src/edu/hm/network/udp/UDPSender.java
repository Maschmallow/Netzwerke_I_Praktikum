package edu.hm.network.udp;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class UDPSender implements Sender {
	private InetAddress inetAddress;
	private int port;
	private DatagramSocket serverSocket;
	
	public UDPSender() {
	}
	
	@Override
	public void send(byte[] sendData) {
		DatagramPacket sendPacket = 
				new DatagramPacket(sendData, sendData.length, inetAddress, port);
		try {
			serverSocket.send(sendPacket);
		} catch (IOException e1) {
			e1.printStackTrace();
		}
	}

	@Override
	public void initalize(InetAddress inetAddress, int port) {
		this.inetAddress = inetAddress;
		this.port = port;
		try {
			serverSocket = new DatagramSocket(port);
		} catch (SocketException e2) {
			e2.printStackTrace();
		}
	}

	@Override
	public void close() {
		serverSocket.close();
	}
}
