package edu.hm.network.udp;

import java.io.IOException;
import java.net.SocketException;
import java.net.SocketTimeoutException;

public interface Receiver {
	MyPacket receive() throws IOException, SocketTimeoutException;
	void close();
	void setTimeoutTime(int timeout) throws SocketException;
}
