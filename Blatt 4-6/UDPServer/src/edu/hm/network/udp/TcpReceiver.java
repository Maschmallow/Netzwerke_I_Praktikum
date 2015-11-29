package edu.hm.network.udp;

import java.io.DataInputStream;
import java.io.EOFException;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.net.SocketTimeoutException;

public class TcpReceiver implements Receiver {
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
			accept();
		} catch(IOException e1) {
			System.err.println("Error: SocketException in TcpReceiver()");
			e1.printStackTrace();
		}
	}

	@Override
	public void setTimeoutTime(int timeout) throws SocketException {
		clientSocket.setSoTimeout(timeout);
	}
	
	@Override
	public void close() {
		try {
			clientSocket.close();
		} catch (IOException e2) {
			e2.printStackTrace();
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
		
		DataInputStream inFromClient = new DataInputStream(clientSocket.getInputStream());
		
		try {
		inFromClient.readFully(receiveData);
		} catch(EOFException e)
		{
			throw new SocketTimeoutException();
		}
		
		MyPacket myPacket = MyPacket.deserializePacket(receiveData);
		
		return myPacket;

	}

	
}
