package edu.hm.network.udp;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.Serializable;

public class MyPacket implements Serializable {
	private static final long serialVersionUID = -2076777123074667668L;
	private int instanceCounter;
	@SuppressWarnings("unused")
	private byte[] unused;
	private int length;

	public MyPacket() {
		unused = new byte[1400];
		this.length = 0;
		this.instanceCounter = 0;
	}

	public void setLength(int length) {
		this.length = length;
	}

	public int getLength() {
		return length;
	}
	
	public int getInstanceCounter() {
		return instanceCounter;
	}

	public static MyPacket deserializePacket(byte[] receiveData) throws IOException {
		ObjectInputStream iStream = new ObjectInputStream(new ByteArrayInputStream(receiveData));
		MyPacket udpPacket;
		try {
			udpPacket = (MyPacket)iStream.readObject();
			// set the length of the received data
			udpPacket.setLength(receiveData.length);
			return udpPacket;
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
		finally {
			iStream.close();
		}
		return null;
	}
}
