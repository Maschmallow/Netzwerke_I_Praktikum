package edu.hm.network.udp;

import java.io.ByteArrayOutputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.Arrays;

public class MyPacket implements Serializable {
	private static final long serialVersionUID = -2076777123074667668L;
	
	private final static int SERIALIZABLE_OVERHEAD = 120;
	
	private static int id = 0;
	@SuppressWarnings("unused")
	private int instanceCounter;
	private byte[] unused;
	@SuppressWarnings("unused")
	private int length;
	
	MyPacket(int sizeOfPacket) {
		instanceCounter = id;
		id++;
		int PacketSize = sizeOfPacket-SERIALIZABLE_OVERHEAD;
		unused = new byte[PacketSize];
		Arrays.fill(unused, (byte)0);
		length = 0;
	}
	
	public int getInstanceCounter() {
		return id;
	}
	
	public static byte[] serializeUDPPacket(MyPacket udpPacket) {
		try {
			ByteArrayOutputStream baos = new ByteArrayOutputStream(1400);
			ObjectOutputStream oos = new ObjectOutputStream(baos);
			oos.writeObject(udpPacket);
			oos.close();
			byte[] ret = baos.toByteArray();
			baos.close();
			return ret;
		} catch(Exception e) {
			e.printStackTrace();
		}
		return null;
	}
}
