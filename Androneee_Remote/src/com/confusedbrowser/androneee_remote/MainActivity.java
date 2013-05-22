package com.confusedbrowser.androneee_remote;

import android.os.Bundle;
import android.view.MenuItem;
import android.view.WindowManager;
import android.view.Menu;
import android.content.Intent;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentTransaction;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.SeekBar;
import java.net.*;
import java.util.Observable;
import java.util.Observer;

import com.confusedbrowser.androneee_remote.fragment.*;

public class MainActivity extends FragmentActivity implements SeekBar.OnSeekBarChangeListener, Observer{
    
	String ipAddress;
    public static final String PREFS_NAME = "preferences";
    SeekBar mSeekBar;
    TextView mProgressText;
    InetAddress serverAddr;
    SendControlsThread sendControls;
    LinearLayout Hud;
    
    HudFragment fragment_hud;
    LogFragment fragment_log;
    
    //VehicleStatusThread vehicleStatus;
    public PhonePosition phonePos;
	
    @Override
    protected void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        
        // Keep our screen constantly on
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        
        // Set the XML view for this activity
        setContentView(R.layout.activity_main);
        
        fragment_hud = new HudFragment();
        fragment_log = new LogFragment();
        
        //Set the initial view to our Hud
        android.support.v4.app.FragmentManager fm = getSupportFragmentManager();
        FragmentTransaction ft = fm.beginTransaction();
        ft.add(R.id.fragment_content, fragment_hud);
        ft.commit();
        
        
        /*vehicleStatus = new VehicleStatusThread(ipAddress, 2047);
        vehicleStatus.start();*/
        
        // Set up slider control to pass to sendControls
        //mProgressText = (TextView)findViewById(R.id.serverPos);
        //mSeekBar = (SeekBar)findViewById(R.id.servoBar);
        //mSeekBar.setOnSeekBarChangeListener(this);
        
        phonePos = new PhonePosition(getBaseContext());
        phonePos.addObserver (this);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) 
    {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        
    	android.support.v4.app.FragmentManager fm = getSupportFragmentManager();
    	FragmentTransaction ft = fm.beginTransaction();
 	   
    	// Handle item selection
        switch (item.getItemId()) 
        {
            case R.id.action_dot_settings:
                Intent settingsActivity = new Intent(getBaseContext(), Preferences.class);
                startActivity(settingsActivity);
                return true;
            case R.id.action_menu_hud:
	     	    ft.replace(R.id.fragment_content, fragment_hud);
	     	    ft.commit();
            	return true;
            case R.id.action_menu_log:
	     	    ft.replace(R.id.fragment_content, fragment_log);
	     	    ft.commit();
            	return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }
    
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromTouch) 
    {
        //mProgressText.setText(progress+"");
    }
 
    public void onStartTrackingTouch(SeekBar seekBar) 
    {
    	//mProgressText.setText(getString(R.string.seekbar_tracking_on));
    }
 
    public void onStopTrackingTouch(SeekBar seekBar) 
    {
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
        //vehicleStatus.stop_listening();
        //this.finish();
    }

    @Override
    public void update(Observable o, Object arg) 
    {
       fragment_hud.update(o, arg);
    }
}
