package edu.hm.pmasch.network;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.StringTokenizer;

public class HttpServ {

	public static void main(String[] args) throws IOException {
      ServerSocket servSocket = null;
      
      
      try {
      	servSocket = new ServerSocket(9004);
      } 
      catch(Exception e){
      	System.out.println("Fehler beim Erzeugen des ServerSockets");
      	return;
      }
      
		while(true)
      {
			try {
				System.out.println("Warte auf Clienten...");
				String filename = "datei";
				Socket connection = servSocket.accept();
				
				DataInputStream in = new DataInputStream(
						new BufferedInputStream(connection.getInputStream()));
				
				long startTime = System.nanoTime();
				
				int headerLength = in.readInt();
				int contentLength = in.readInt();
				
				System.out.println(headerLength);
				System.out.println(contentLength);
				
				byte[] headBuf = new byte[headerLength];
				for (int i = 0; i < headerLength;) {
					int read = in.read(headBuf,i,headerLength-i);
					if (read > 0) i +=read;
				}
				
				byte[] contentBuf = new byte[contentLength];
				for (int i = 0; i < contentLength;) {
					 int read = in.read(contentBuf,i,contentLength-i);
					 if (read > 0) i +=read;
				}
				
				long endTime = System.nanoTime();
				
				long duration = endTime - startTime;
				
				System.out.println("Die ‹bertragung ¸ber tcp dauerte: " 
						+ (double)duration/1000000000.0 
						+ " Sekunden.");
				
				BufferedReader reader = new BufferedReader(
						new InputStreamReader(
								new ByteArrayInputStream(headBuf), "ASCII"));
				String firstLine = reader.readLine();
				StringTokenizer tokenizer = new StringTokenizer(firstLine);
				if(tokenizer.nextToken().equals("PUT")) {
					filename = tokenizer.nextToken();
				}
				
				Path file = Paths.get(filename);
				Files.write(file, contentBuf);
				
			} catch (Exception e) {
				System.out.println(e);
				System.out.println("=> Schlieﬂe Verbindung");
			}

      }
	}
	
}
