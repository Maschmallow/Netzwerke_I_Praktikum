package edu.hm.network.udp;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.Socket;

public class TCPSender implements Sender {
	private Socket clientSocket;
	
	public TCPSender() {
		
	}

	@Override
	public void send(byte[] sendData) {
		try {
			OutputStream out = clientSocket.getOutputStream();
			DataOutputStream charOut = new DataOutputStream(out);
			charOut.write(sendData);
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