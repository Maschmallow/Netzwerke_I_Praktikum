package edu.hm.network.udp;

import java.io.ByteArrayOutputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.Arrays;

public class OwnUDPPacket implements Serializable {
	private static final long serialVersionUID = -8707352964590510292L;
	
	private static int id = 0;
	private int instanceCounter;
	private byte[] unused;
	OwnUDPPacket() {
		instanceCounter = id;
		id++;
		unused = new byte[1196];
		Arrays.fill(unused, (byte)0);
	}
	
	public byte[] serializeUDPPacket(OwnUDPPacket udpPacket) {
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
