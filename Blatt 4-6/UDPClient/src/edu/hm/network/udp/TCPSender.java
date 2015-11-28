package edu.hm.network.udp;

import java.io.DataOutputStream;
import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;

public class TCPSender implements Sender {
	private Socket clientSocket;
	
	public TCPSender() {
		
	}

	@Override
	public void send(byte[] sendData) {
		try {
			DataOutputStream charOut = 
					new DataOutputStream(clientSocket.getOutputStream());
			charOut.write(sendData);
			charOut.flush();
		} catch(IOException e1) {
			e1.printStackTrace();
		}
	}
	
	@Override
	public void initalize(InetAddress ipAddress, int port) {
		try {
			clientSocket = new Socket(ipAddress, port);
			System.out.println("Connected to: " + clientSocket.getInetAddress().getHostName());
		} catch(IOException e1) {
			e1.printStackTrace();
		}
	}

	@Override
	public void close() {
		try {
			clientSocket.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}