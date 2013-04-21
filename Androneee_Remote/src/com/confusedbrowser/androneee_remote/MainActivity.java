package com.confusedbrowser.androneee_remote;

import android.os.Bundle;
import android.view.View;
import android.app.Activity;
import android.view.Menu;
import android.content.Intent;
import android.widget.EditText;
import android.util.Log;
import android.widget.TextView;

import java.io.*;
import java.net.*;

public class MainActivity extends Activity {
	
	public final static String EXTRA_MESSAGE = "com.example.myfirstapp.MESSAGE";
	InetAddress serverAddr;
	TextView t;
	
	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        Thread thread = new Thread(new Runnable(){
            @Override
            public void run() {
                try {
	       	         DatagramSocket clientSocket = new DatagramSocket();
	    	         InetAddress IPAddress = InetAddress.getByName("54.246.151.139");
	    	         byte[] receiveData = new byte[1024];
	    	         String sentence = "Hello from Daves Galaxy Nexus\n";
	    	         byte[] sendData = sentence.getBytes("US-ASCII");
	    	         DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, 2047);
	    	         clientSocket.send(sendPacket);
	    	         DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
	    	         clientSocket.receive(receivePacket);
	    	         String modifiedSentence = new String(receivePacket.getData());
	    	         Log.d("shahmirj", "FROM SERVER:" + modifiedSentence);
	    	         TextView t = new TextView(MainActivity.this); 
	    	         t=(TextView)findViewById(R.id.server_message); 
	    	         t.setText(modifiedSentence);
	    	         
	    	         clientSocket.close();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });

        thread.start(); 

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
}
