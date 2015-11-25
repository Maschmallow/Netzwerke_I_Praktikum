package edu.hm.network.udp;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;

public class OwnUDPPacket {
	private int instanceCounter;
	private int length;
	private byte[] unused;
	
	public OwnUDPPacket() {
	    unused = new byte[1400-8-8];
	}
	
	public void setLength(int length) {
	    this.length = length;
	}
	
	public int getLength() {
	    return length;
	}
	
	public static OwnUDPPacket deserializeUDPPacket(byte[] receiveData) throws IOException {
	    ObjectInputStream iStream = new ObjectInputStream(new ByteArrayInputStream(receiveData));
        OwnUDPPacket udpPacket;
        try {
            udpPacket = (OwnUDPPacket)iStream.readObject();
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
