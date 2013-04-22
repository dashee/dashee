package com.confusedbrowser.androneee_remote;

import android.os.Bundle;
import android.view.View;
import android.app.Activity;
import android.view.Menu;
import android.content.Intent;
import android.content.Context;
import android.widget.EditText;
import android.util.Log;
import android.widget.TextView;

import java.io.*;
import java.net.*;

public class UDP_thread extends Thread {
	
	String ip_address;
	int port_num;
	Context main_context;
	String position;

	public UDP_thread(Context context, String ip, int port, String position)
	{
		super();
		ip_address = ip;
		port_num = port;
		main_context = context;
		this.position = position;
	}
	
	public void run() 
    {    			
	 try {
		 DatagramSocket clientSocket = new DatagramSocket();
		 InetAddress IPAddress = InetAddress.getByName(ip_address);
		 byte[] receiveData = new byte[1024];
		 String sentence = this.position+"\n";
		 byte[] sendData = sentence.getBytes("US-ASCII");
		 DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, port_num);
		 clientSocket.send(sendPacket);
		 DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
		 clientSocket.receive(receivePacket);
		 String modifiedSentence = new String(receivePacket.getData());
		 Log.d("shahmirj", "FROM SERVER:" + modifiedSentence);
		 /*TextView t = new TextView(MainActivity.this); 
		 t= main_context.findViewById(R.id.server_message); 
		 t.setText(modifiedSentence);*/
		 clientSocket.close();
	 } catch (Exception e) {
		 e.printStackTrace();
	 }
    }
    
}
