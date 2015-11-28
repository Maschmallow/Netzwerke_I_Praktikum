package edu.hm.network.udp;

import java.net.InetAddress;

public interface Sender {
	public void initalize(InetAddress inetAddress, int port);
	public void send(byte[] sendData);
	public void close();
};
