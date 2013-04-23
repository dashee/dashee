package com.confusedbrowser.androneee_remote;

import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;
import android.view.View;
import android.app.Activity;
import android.view.Menu;
import android.content.Intent;
import android.widget.EditText;
import android.util.Log;
import android.widget.TextView;
import android.widget.SeekBar;

import java.io.*;
import java.net.*;

public class MainActivity extends Activity implements SeekBar.OnSeekBarChangeListener {
	
	SeekBar mSeekBar;
    TextView mProgressText;
	InetAddress serverAddr;
	SendControlsThread sendControls;
	VehicleStatusThread vehicleStatus;
	
	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        // Remove title and go full screen
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
        WindowManager.LayoutParams.FLAG_FULLSCREEN);
        
        // Set the XML view for this activity
        setContentView(R.layout.activity_main);
        
        // Create threads for send and receiving data from the vehicle  
        sendControls = new SendControlsThread(this, "192.168.1.12", 2047, 50);
        sendControls.start();
        
        vehicleStatus = new VehicleStatusThread("192.168.1.12", 2047);
        vehicleStatus.start();
        
        // Set up slider control to pass to sendControls
        mProgressText = (TextView)findViewById(R.id.serverPos);
        mSeekBar = (SeekBar)findViewById(R.id.servoBar);
        mSeekBar.setOnSeekBarChangeListener(this);

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromTouch) {
    	sendControls.setPosition(progress);
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
	}

	protected void onStop()
	{
		super.onStop();
		sendControls.stop_sending();
		vehicleStatus.stop_listening();
		this.finish();
	}
    
}
