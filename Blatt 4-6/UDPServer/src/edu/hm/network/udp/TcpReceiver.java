package edu.hm.network.udp;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.net.SocketTimeoutException;
import java.nio.ByteBuffer;

public class TcpReceiver {
	private ServerSocket serverSocket;
	private Socket clientSocket;
	private boolean isVerbose;
	private BufferedReader charIn;

	public TcpReceiver(int port, boolean verbose) {
		try {
			serverSocket = new ServerSocket(port);
			System.out.println("**** TCP server started ****");
			System.out.println("The server is listening on port: " + port);
			System.out.println("The server is waiting for client connections.");
			isVerbose = verbose;
		} catch(IOException e1) {
			e1.printStackTrace();
		}
	}

	public void setTimeout(int timeout) throws SocketException {
		clientSocket.setSoTimeout(timeout);
	}
	
	public void close() {
		try {
			din.close();
			clientSocket.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	public void accept() {
		try {
			clientSocket = serverSocket.accept();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	public MyPacket receive() throws IOException,SocketTimeoutException {
		byte[] receiveData = new byte[1400];

		if (isVerbose) {
			System.out.println("Verbindung wurde von: " + 
					clientSocket.getInetAddress().
					getHostName() + "aufgebaut.");
		}
		
		ByteBuffer bf = ByteBuffer.allocate(1400);
		BufferedInputStream inFromClient = new BufferedInputStream(clientSocket.getInputStream());
		int num = 0;
		while(true) {
			int b = inFromClient.read();
			if (b== -1) {
				break;
			}
			bf.put((byte)b);
			num++;
		}
		
		MyPacket myPacket = MyPacket.deserializePacket(receiveData);
		myPacket.setLength(num);

		return myPacket;

	}
}
