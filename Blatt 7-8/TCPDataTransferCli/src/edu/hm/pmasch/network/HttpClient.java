package edu.hm.pmasch.network;

import java.io.BufferedOutputStream;
import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

public class HttpClient {
	private byte[] header;
	private byte[] content;

	private Socket clientSocket;
	
	public HttpClient(String filename, String targethost, String contentType,  int serverPort)
	      throws UnknownHostException, IOException {
		this.content = readInFile(filename);
		
		String header = "PUT " + filename + " HTTP/1.1\r\n"
			+ "Host: " + targethost + "\r\n"
	      + "Connection: keep-alive\r\n" 
			+ "Content-length: " + this.content.length + "\r\n"
			+ "Content-Type: " + contentType + "\r\n\r\n";
		
		this.header = header.getBytes("ASCII");
		
		clientSocket = new Socket(InetAddress.getByName(targethost), serverPort);
	}
	
	public void start() {
			try {
				System.out.println("Aufbau der Verbindung");
				
				DataOutputStream out = new DataOutputStream(
						new BufferedOutputStream(
								clientSocket.getOutputStream()));
				out.writeInt(header.length);
				out.writeInt(content.length);
				out.write(header);
				out.write(content);
				out.flush();
				
			} catch (IOException e) {
				System.out.println(e);
			}
	}
	
	public byte[] readInFile(String filename) throws IOException {
		InputStream in = new FileInputStream(filename);
		ByteArrayOutputStream out = new ByteArrayOutputStream();
		int b;
		while ((b = in.read()) != -1) out.write(b);
		return out.toByteArray();
	}

	public static void main(String[] args) {
		try {
			String contentType = "";
			if (args[0].endsWith(".jpg") || args[0].endsWith(".jpeg"))
				contentType = "image/jpeg";
			else if (args[0].endsWith(".pdf"))
				contentType = "application/pdf";
			
			HttpClient client = new HttpClient(args[0], args[1], contentType, 9004);
			client.start();
		} catch(ArrayIndexOutOfBoundsException ex) {
			System.out.println("Usage: java HttpClient filename targethost");
		}
		catch (IOException e) {
			System.out.println("Usage: java HttpClient filename targethost");
		}
		catch (Exception e) {
			System.out.println(e);
		}
	}
}
