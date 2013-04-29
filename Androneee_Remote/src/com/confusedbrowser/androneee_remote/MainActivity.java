package com.confusedbrowser.androneee_remote;

import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;
import android.view.View;
import android.app.Activity;
import android.view.Menu;
import android.content.Context;
import android.content.Intent;
import android.widget.EditText;
import android.util.Log;
import android.widget.TextView;
import android.widget.SeekBar;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.hardware.Sensor;

import java.io.*;
import java.net.*;
import java.util.Observable;
import java.util.Observer;

public class MainActivity extends Activity implements SeekBar.OnSeekBarChangeListener, Observer{
	
	static String ipAddress = "192.168.0.11";
	SeekBar mSeekBar;
    TextView mProgressText;
	InetAddress serverAddr;
	SendControlsThread sendControls;
	//VehicleStatusThread vehicleStatus;
	public PhonePosition phonePos;
	
	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // Remove title and go full screen
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
        WindowManager.LayoutParams.FLAG_FULLSCREEN);
        Log.d("androneee", "starting");
        // Set the XML view for this activity
        setContentView(R.layout.activity_main);
        
        // Create threads for send and receiving data from the vehicle  
        sendControls = new SendControlsThread(this, ipAddress, 2047, 50);
        sendControls.start();
        
        /*vehicleStatus = new VehicleStatusThread(ipAddress, 2047);
        vehicleStatus.start();*/
        
        // Set up slider control to pass to sendControls
        mProgressText = (TextView)findViewById(R.id.serverPos);
        mSeekBar = (SeekBar)findViewById(R.id.servoBar);
        mSeekBar.setOnSeekBarChangeListener(this);
        
        phonePos = new PhonePosition(getBaseContext());
        phonePos.addObserver (this);
    }
	
	public void wheelPos(int pos){
		mSeekBar.setProgress(pos);
        sendControls.setPosition(pos);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromTouch) {
	 	mProgressText.setText(progress+"");
    }
 
    public void onStartTrackingTouch(SeekBar seekBar) {
    	//mProgressText.setText(getString(R.string.seekbar_tracking_on));
    }
 
    public void onStopTrackingTouch(SeekBar seekBar) {
        //mTrackingText.setText(getString(R.string.seekbar_tracking_off));
    }
    
    @Override
	protected void onResume() 
	{
		super.onResume();
		phonePos.monitor();
	}
    
    protected void onPause() {
        super.onPause();
        phonePos.stopMonitor();
    }

	protected void onStop()
	{
		super.onStop();
		sendControls.stop_sending();
		//vehicleStatus.stop_listening();
		this.finish();
	}

	@Override
	public void update(Observable o, Object arg) {
		PhonePosition pp = (PhonePosition) o;
		int progress = (int)mapping(-pp.roll_val,-0.523,0.523,0,100);
        wheelPos(progress);
	}
	
	public double mapping(float value, double leftMin, double leftMax, double rightMin, double rightMax){
		
        //Figure out how 'wide' each range is
		double leftSpan = leftMax - leftMin;
		double rightSpan = rightMax - rightMin;
        //Convert the left range into a 0-1 range (float)
		double valueScaled = (value - leftMin) / (leftSpan);
        //Convert the 0-1 range into a value in the right range.
		if(value<leftMin) return rightMin;
		if(value>leftMax) return rightMax;
        return rightMin + (valueScaled * rightSpan); 
    }
    
}
