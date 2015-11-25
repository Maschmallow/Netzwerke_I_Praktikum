package edu.hm.network.udp;

import java.io.*;
import java.net.*;

public class Client {
	
	public static void main(String[] args) throws Exception {
		boolean useTCP = false;
			BufferedReader inFromUser =
					new BufferedReader(new InputStreamReader(System.in));
			InetAddress IPAddress = InetAddress.getByName("localhost");
			String sentence = inFromUser.readLine();
			
			if (useTCP){
				Socket socket = new Socket("", PortNumber);
			}
			else {
				OwnUDPPacket sendData = new OwnUDPPacket();
				ObjectOutputStream s = new ObjectOutputStream(OwnUDPPacket);
				DatagramPacket sendPacket = new DatagramPacket(sendData, sendData., IPAddress, 9876);
				DatagramSocket clientSocket = new DatagramSocket();
				clientSocket.send(sendPacket);
				clientSocket.close();
			}
	}

}
