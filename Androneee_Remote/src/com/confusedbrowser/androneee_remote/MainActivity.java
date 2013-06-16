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

/**
 * The main activity that the program will run.
 * This will set our fragments, handel our preferences
 * changing, start the threads which commnicate to our servers
 * set and listen to the Observers so actions can be taken when things are changed
 *
 * @author David Buttar
 * @author Shahmir Javaid
 */
public class MainActivity 
    extends FragmentActivity 
    implements SeekBar.OnSeekBarChangeListener, Observer
{

    /**
     * Create instances of our fragments in memeory.
     * So they dont have to be initialized every time, and hold
     * there previous state.
     */
    HudFragment fragment_hud;
    LogFragment fragment_log;
    
    /**
     * This is our thread_servo, which allows us to communicate
     * with our server on the RC robot, this thread handles the
     * network communication
     */
    public SendControlsThread thread_servo;
    
    /**
     * Handel to our Phone schemetics. This will return
     * our Phoneposition, by adding an observer
     */
    public PhonePosition phonePos;

    private OnSharedPreferenceChangeListener settingChangeListener;
	
    @Override
    protected void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        
        // Keep our screen constantly on
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        
        // Set the XML view for this activity
        setContentView(R.layout.activity_main);
        
        // Create our fragment views
        fragment_hud = new HudFragment();
        fragment_log = new LogFragment();
        
        //Set the initial view to our HUD
        FragmentTransaction ft = getSupportFragmentManager().beginTransaction();
        ft.add(R.id.fragment_content, fragment_hud);
        ft.commit();
        
        // This will initialise our PhonePosition Observer,
        // So our this.update function can handle updates 
        phonePos = new PhonePosition(getBaseContext());
        phonePos.addObserver(this);
    	
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);

        // Initialize our thread
        thread_servo = new SendControlsThread(this, prefs.getString("pref_ip", "192.168.1.12"), 2047, 50);
        thread_servo.start();
        
        // Add the settings listener events
        addSettingListener();
    }
    
    /**
     *  Add and register setting listeners. Create our 
     *  listeners for when the property is changed, do a provided action. For example
     *  when the IP is changed. Make sure you tell the servo this has been done
     */
    public void addSettingListener() 
    {
    	SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);

    	// Instance field for listener
        settingChangeListener = new SharedPreferences.OnSharedPreferenceChangeListener() 
        {
            public void onSharedPreferenceChanged(SharedPreferences prefs, String key) 
            {
                thread_servo.setIp(prefs.getString("pref_ip", "192.168.1.11"));
            }
    	};
        prefs.registerOnSharedPreferenceChangeListener(settingChangeListener);
    }

    /**
     * Set our menue on the top bar. This will add the HUD, LOG and the ... icon
     * to the top of our menue bar
     *
     * @param menu - The menu object to load
     * @return boolean - Always true
     */
    @Override
    public boolean onCreateOptionsMenu(Menu menu) 
    {
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
    /**
     * Handle our menu button clicks. Given the menue item, 
     * either start an activity or change the fragment view
     *
     * @param item - The handler to the item selected
     *
     * @return boolean - true if clicked, or super.onOptionsItemSelected(item);
     */
    public boolean onOptionsItemSelected(MenuItem item) 
    {
    	// Handle item selection
        switch (item.getItemId()) 
        {
            case R.id.action_dot_settings:
            {
                Intent settingsActivity = new Intent(getBaseContext(), PreferencesActivity.class);
                startActivity(settingsActivity);
                return true;
            }
            case R.id.action_menu_hud:
            {
                FragmentTransaction ft = getSupportFragmentManager().beginTransaction();
                ft.replace(R.id.fragment_content, fragment_hud);
                ft.commit();
            	return true;
            }
            case R.id.action_menu_log:
            {
                FragmentTransaction ft = getSupportFragmentManager().beginTransaction();
                ft.replace(R.id.fragment_content, fragment_log);
                ft.commit();
            	return true;
            }
            default:
                return super.onOptionsItemSelected(item);
        }        
    }
    
    /**
     * App is Resumed from a pause state.
     * Resume the thread, and start the PhoneRoll monitoring
     */
    @Override
    protected void onResume() 
    {
        super.onResume();
        phonePos.onResume();
        thread_servo.onResume();
    }
    
    /**
     * App is paused, handel pause systems.
     * Pause the thread, and stop the PhoneRoll monitoring
     */
    @Override
    protected void onPause() {
        super.onPause();
        phonePos.onPause();
        thread_servo.onPause();
    }

    @Override
    /**
     * Stop everything. Time to go to bed
     */
    protected void onStop()
    {
        super.onStop();
    }

    /**
     *  Update our view and model. Given the phone's roll
     *  we update our server/model using our thread and we also
     *  update the HUD rotational value
     *  
     *  @param o - The observer handler
     *  @param arg - The arguments to the Observer
     */
    @Override
    public void update(Observable o, Object arg) 
    {
        PhonePosition position = (PhonePosition) o;
        double progress = remapValue(-position.getRoll(),-0.523,0.523,0,100);
        
        thread_servo.setPosition((int)progress);
        fragment_hud.rotateHud((float)progress);
    }
    
    /**
     * Generic function. Takes a numeric value which is a value in the curMin to curMax range
     * and converts it to a corresponding value in the targetMin to targetMax range.
     * @param value - The numeric value to be re-mapped
     * @param curMin - Current range min
     * @param curMax - Current range max
     * @param targetMin - Current range min
     * @param targetMax - Current range max
     *
     * @return double - Value mapped to the new target range
     */
    public double remapValue(float value, double curMin, double curMax, double targetMin, double targetMax)
    {
        //Figure out how 'wide' each range is
        double leftSpan = curMax - curMin;
        double rightSpan = targetMax - targetMin;
        
        //Convert the left range into a 0-1 range (float)
        double valueScaled = (value - curMin) / (leftSpan);
        
        //Convert the 0-1 range into a value in the right range.
        if(value<curMin) return targetMin;
        if(value>curMax) return targetMax;
        return targetMin + (valueScaled * rightSpan); 
    }

    @Override
    public void onStartTrackingTouch(SeekBar arg0) 
    {
    }

    @Override
    public void onStopTrackingTouch(SeekBar arg0) 
    {
    }

    @Override
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) 
    {
    }
}
