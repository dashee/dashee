package com.confusedbrowser.androneee_remote;

import android.os.Bundle;
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
	UDP_thread connection;
	
	@Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        //servoBar
        mProgressText = (TextView)findViewById(R.id.serverPos);
        mSeekBar = (SeekBar)findViewById(R.id.servoBar);
        mSeekBar.setOnSeekBarChangeListener(this);
        
        connection = new UDP_thread(this, "192.168.1.12", 2047, 50);
		connection.start();
        /*connection = new UDP_thread(this, "192.168.1.12", 2047);
        connection.start();*/
        // Android is shite!!!
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromTouch) {
    	connection.setPosition(progress);
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
		connection.stop_sending();
		this.finish();
	}
    
}
