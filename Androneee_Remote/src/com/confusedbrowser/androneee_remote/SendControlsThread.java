package com.confusedbrowser.androneee_remote;

import android.content.Context;
import android.util.Log;
import java.net.*;

public class SendControlsThread extends Thread {
	
	String ip_address;
	int port_num;
	Context main_context;
	int position;
	int prevPos;
	DatagramSocket clientSocket;
	InetAddress IPAddress;
	private Object mPauseLock;
	private boolean mPaused;
    private boolean mFinished;
    private int timeOut = 500; // Time to send same value again
    private long timeValueSent = 0; // Time when last value was set

	public SendControlsThread(Context context, String ip, int port, int position)
	{
		super();
		ip_address = ip;
		mPauseLock = new Object();
        mPaused = false;
        mFinished = false;
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
	
	public void setIp(String ip){
		ip_address = ip;
		try {
			IPAddress = InetAddress.getByName(ip_address);
		}catch (Exception e) {
			 e.printStackTrace();
		}
	}
	
	public void run() 
    {    
		while(!mFinished){
			long curTime = System.currentTimeMillis();
			if(this.position != this.prevPos || (curTime-timeValueSent > timeOut)){
				 try {
                     byte sendData[] = new byte[]{ 17, (byte)(this.position << 1) };

					 //String sentence = this.position+"\n";
					 //byte[] sendData = sentence.getBytes("US-ASCII");
					 DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, port_num);
					 clientSocket.send(sendPacket);
					 timeValueSent = System.currentTimeMillis();
					 //Log.d("androneee", "Time Diff: "+timeValueSent);
					 /*TextView t = new TextView(MainActivity.this);
					 t= main_context.findViewById(R.id.server_message);
					 t.setText(modifiedSentence);*/
				 } catch (Exception e) {
					 e.printStackTrace();
				 }
				 this.prevPos = this.position;
			}
			
			synchronized (mPauseLock) {
	            while (mPaused) {
	                try {
	                    mPauseLock.wait();
	                } catch (InterruptedException e) {
	                }
	            }
	        }
		}
    }
	
	/**
     * Call this on pause.
     */
    public void onPause() {
        synchronized (mPauseLock) {
            mPaused = true;
        }
    }

    /**
     * Call this on resume.
     */
    public void onResume() {
        synchronized (mPauseLock) {
            mPaused = false;
            mPauseLock.notifyAll();
        }
    }
	
	public void start_sending(){
		
	}
    
}
