package com.confusedbrowser.androneee_remote;

import android.os.Bundle;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.MenuItem;
import android.view.WindowManager;
import android.view.Menu;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.OnSharedPreferenceChangeListener;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentTransaction;
import android.widget.SeekBar;
import java.util.Observable;
import java.util.Observer;
import com.confusedbrowser.androneee_remote.fragment.*;

public class MainActivity extends FragmentActivity implements SeekBar.OnSeekBarChangeListener, Observer{
       
    HudFragment fragment_hud;
    LogFragment fragment_log;
    OnSharedPreferenceChangeListener settingChangeListener;
    
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
        
        //Set the initial view to our HUD
        android.support.v4.app.FragmentManager fm = getSupportFragmentManager();
        FragmentTransaction ft = fm.beginTransaction();
        ft.add(R.id.fragment_content, fragment_hud);
        ft.commit();
        
        // This will initialise our PhonePosition Observer,
        // So our this.update function can handle updates 
        phonePos = new PhonePosition(getBaseContext());
        phonePos.addObserver (this);
        
        addSettingListener();
        
    }
    
    // We not only want to store setting we want to enact them realtime
    public void addSettingListener() 
    {
    	SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
    	// Instance field for listener
        settingChangeListener = new SharedPreferences.OnSharedPreferenceChangeListener() {
    	  public void onSharedPreferenceChanged(SharedPreferences prefs, String key) {
    		  Log.d("androneee", key);
    		  fragment_hud.setIp(prefs.getString("pref_ip", "192.168.0.11"));
    		  showUserSettings();
    	  }
    	};

        prefs.registerOnSharedPreferenceChangeListener(settingChangeListener);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) 
    {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    public boolean onOptionsItemSelected(MenuItem item) 
    {
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
    
    private void showUserSettings() {
    	SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);
        String ip_address = prefs.getString("pref_ip", "192.168.0.11");
        Log.d("androneee", "New ip address setting: "+ip_address);
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
    }

    @Override
    public void update(Observable o, Object arg) 
    {
       fragment_hud.update(o, arg);
    }


	@Override
	public void onStartTrackingTouch(SeekBar arg0) 
	{
		// TODO Auto-generated method stub
	}

	@Override
	public void onStopTrackingTouch(SeekBar arg0) 
	{
		// TODO Auto-generated method stub
	}

	@Override
	public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) 
	{
		// TODO Auto-generated method stub	
	}
}
