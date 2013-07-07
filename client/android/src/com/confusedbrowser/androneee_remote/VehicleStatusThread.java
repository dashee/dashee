package com.confusedbrowser.androneee_remote;

import android.util.Log;
import java.net.*;

public class VehicleStatusThread extends Thread {
	
	String ip_address;
	int port_num;
	DatagramSocket clientSocket;
	InetAddress IPAddress;

	public VehicleStatusThread(String ip, int port)
	{
		super();
		ip_address = ip;		
		port_num = port;

		try {
			IPAddress = InetAddress.getByName(ip_address);
			clientSocket = new DatagramSocket();
		}catch (Exception e) {
			 e.printStackTrace();
		}
	}
	
	public void run() 
    {    
		while(true){
			 try {
				 byte[] receiveData = new byte[1024];
				 String sentence = "0\n";
				 byte[] sendData = sentence.getBytes("US-ASCII");
				 DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, port_num);
				 clientSocket.send(sendPacket);
				 DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
				 clientSocket.receive(receivePacket);
				 String modifiedSentence = new String(receivePacket.getData());
				 Log.d("shahmirj", "FROM SERVER:" + modifiedSentence);
			 } catch (Exception e) {
				 e.printStackTrace();
			 }
		}
    }
	
	public void stop_listening(){
		clientSocket.close();
	}
    
}
