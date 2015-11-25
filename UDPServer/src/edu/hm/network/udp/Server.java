package edu.hm.network.udp;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {

	private static final int PORT_NUMBER = 9876;
	public static void main(String[] args) throws Exception {
		byte[] receiveData = new byte[1024];
		byte[] sendData = new byte[1024];
		boolean isTCPConnection = false;
		if (isTCPConnection)
		{
			try {
				ServerSocket serverSocket = new ServerSocket(PORT_NUMBER);
				Socket clientSocket = null;
				try {
					clientSocket = serverSocket.accept();
				} catch()
			} catch (IOException e) {
	           System.out.println(e);
	      }
		} else {
			DatagramSocket serverSocket = new DatagramSocket(PORT_NUMBER);
			while(true)
			{
				
				else  {
					DatagramPacket receivePacket = 
							new DatagramPacket(receiveData, receiveData.length);
					serverSocket.receive(receivePacket);
					String sentence = new String(receivePacket.getData());
					System.out.println("RECEIVED: " + sentence);
					InetAddress IPAddress = receivePacket.getAddress();
					int port = receivePacket.getPort();
					String capitalizedSentence = sentence.toUpperCase();
					sendData = capitalizedSentence.getBytes();
					DatagramPacket sendPacket = 
							new DatagramPacket(sendData, sendData.length, IPAddress, port);
					serverSocket.send(sendPacket);
				}
			}
		}
	}

}
