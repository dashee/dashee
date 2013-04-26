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

public class SendControlsThread extends Thread {
	
	String ip_address;
	int port_num;
	Context main_context;
	int position;
	int prevPos;
	DatagramSocket clientSocket;
	InetAddress IPAddress;

	public SendControlsThread(Context context, String ip, int port, int position)
	{
		super();
		ip_address = ip;
		
		port_num = port;
		main_context = context;
		this.position = position;
		this.prevPos = position;
		try {
			IPAddress = InetAddress.getByName(ip_address);
			Log.d("androneee", IPAddress.toString());
			clientSocket = new DatagramSocket();
		}catch (Exception e) {
			 e.printStackTrace();
		}
	}
	
	public void setPosition(int position){
		this.position = position;
	}
	
	public void run() 
    {    
		while(true){
			if(this.position != this.prevPos){
				 try {
					 String sentence = this.position+"\n";
					 byte[] sendData = sentence.getBytes("US-ASCII");
					 DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, port_num);
					 clientSocket.send(sendPacket);
					 
					 /*TextView t = new TextView(MainActivity.this); 
					 t= main_context.findViewById(R.id.server_message); 
					 t.setText(modifiedSentence);*/
				 } catch (Exception e) {
					 e.printStackTrace();
				 }
				 this.prevPos = this.position;
			}
		}
    }
	
	public void stop_sending(){
		clientSocket.close();
	}
    
}
