package edu.hm.network.udp;

import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.net.SocketTimeoutException;

public class TcpReceiver {
	private ServerSocket serverSocket;
	private Socket clientSocket;
	private boolean isVerbose;

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

	public MyPacket receive() throws IOException,SocketTimeoutException {
		byte[] receiveData = new byte[1400];
		clientSocket = serverSocket.accept();

		if (isVerbose) {
			System.out.println("Verbindung wurde von: " + 
					clientSocket.getInetAddress().
					getHostName() + "aufgebaut.");
		}

		InputStream in = clientSocket.getInputStream();
		DataInputStream din = new DataInputStream(in);
		din.readFully(receiveData);

		MyPacket myPacket = MyPacket.deserializePacket(receiveData);
		myPacket.setLength(receiveData.length);

		return myPacket;

	}
}
