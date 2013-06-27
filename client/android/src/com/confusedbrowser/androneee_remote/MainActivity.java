package com.confusedbrowser.androneee_remote;

import android.os.Bundle;
import android.preference.PreferenceManager;
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

import com.confusedbrowser.androneee_remote.fragments.*;
import com.confusedbrowser.androneee_remote.models.*;
import com.confusedbrowser.androneee_remote.threads.*;

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
    private FragmentHud fragmentHud;
    private FragmentLog fragmentLog;
    
    /**
     * This is our threadSendControllerPositions, which allows us to communicate
     * with our server on the RC robot, this thread handles the
     * network communication
     */
    public ThreadPassPositionControls threadPassPositionControls;
    
    /**
     * This will poll our server to check wheather it is still
     * alive or not. If not then an observer will be notified
     * It is this observer that will handel other threads, which require
     * this server
     */
    public ThreadCheckServerStatus threadCheckServerStatus;
    
    /**
     * Handel to our Phone schemetics. This will return
     * our phones roll, pitch state, by notifying the observer
     */
    public ModelPhonePosition modelPosition;
    
    /**
     * Hold the state of our Server. This will notify our
     * Observer, any time server values are changed
     */
    public ModelServerState modelServerState;
    
    /**
     * Current vehicle to control
     */
    public ModelVehicle modelVehicle;

    /**
     * The listener, to when the settings have changed.
     * See addSettingsListener() for more init details
     */
    private OnSharedPreferenceChangeListener settingChangeListener;

    @Override
    protected void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        
        // Keep our screen constantly on
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        
        // Set the XML view for this activity
        setContentView(R.layout.activity_main);
        
        // This will initialise our PhonePosition Observer,
        // So our this.update function can handle updates 
        modelPosition = new ModelPhonePosition(getBaseContext());
        modelPosition.addObserver(this);
        
        //Create our ServerState model
        modelServerState = new ModelServerState();
        modelServerState.addObserver(this);
        
        // Create our vehicle model
        modelVehicle = new ModelVehicleCar();
        
        // Create our fragment views
        fragmentHud = new FragmentHud();
        fragmentLog = new FragmentLog();
        
        //Set the initial view to our HUD
        FragmentTransaction ft = getSupportFragmentManager().beginTransaction();
        ft.add(R.id.fragment_content, fragmentHud);
        ft.commit();
    	
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this);

        // Initialise our thread
        threadPassPositionControls = new ThreadPassPositionControls(this.modelServerState, 
        		prefs.getString("pref_ip", "192.168.1.12"), this.modelVehicle);
        threadPassPositionControls.start();

        // Initialise our thread
        threadCheckServerStatus = new ThreadCheckServerStatus(modelServerState, prefs.getString("pref_ip", "192.168.1.12"));
        threadCheckServerStatus.start();
        
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
                threadPassPositionControls.setIp(prefs.getString("pref_ip", "192.168.1.11"));
                threadCheckServerStatus.setIp(prefs.getString("pref_ip", "192.168.1.11"));
                fragmentHud.setHudIp(prefs.getString("pref_ip", "192.168.1.11"));
            }
    	};
        prefs.registerOnSharedPreferenceChangeListener(settingChangeListener);
    }

    /**
     * Set our menu on the top bar. This will add the HUD, LOG and the ... icon
     * to the top of our menu bar
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
                ft.replace(R.id.fragment_content, fragmentHud);
                ft.commit();
            	return true;
            }
            case R.id.action_menu_log:
            {
                FragmentTransaction ft = getSupportFragmentManager().beginTransaction();
                ft.replace(R.id.fragment_content, fragmentLog);
                ft.commit();
            	return true;
            }
            default:
                return super.onOptionsItemSelected(item);
        }        
    }

    /**
     *  Update our view and model. Given the phone's roll
     *  we update our server/model using our thread and we also
     *  update the HUD rotational value
     *  
     *  @param o - The observer handler
     *  @param arg - The arguments to the Observer
     */
    public void update(Observable o, Object arg)
    {
        if (o instanceof ModelPhonePosition)
        {
            ModelPhonePosition position = (ModelPhonePosition)o;
            this.modelVehicle.setFromPhonePosition(position);
            
            float roll = position.getRoll();
            float pitch = position.getPitch();
            fragmentHud.setPosition(roll, pitch);
            fragmentHud.setHudConnection(position.getPitch()+"");
        }

        try
        {
            if (o instanceof ModelServerState)
            {
                ModelServerState serverState = (ModelServerState)o;

                if (serverState.isAlive())
                {
                    runOnUiThread(new Runnable() {
                        public void run()
                        {
                            fragmentHud.setHudConnection("Connected"); 
                        }
                    });
                }
                else
                {
                    runOnUiThread(new Runnable() {
                        public void run()
                        {
                            fragmentHud.setHudConnection("Failed"); 
                        }
                    });
                }
            }
        }
        catch (Exception e)
        {
            e.printStackTrace();
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
        modelPosition.onResume();
        threadPassPositionControls.onResume();
        threadCheckServerStatus.onResume();
    }
    
    /**
     * App is paused, handel pause systems.
     * Pause the thread, and stop the PhoneRoll monitoring
     */
    @Override
    protected void onPause() 
    {
        super.onPause();
        modelPosition.onPause();
        threadPassPositionControls.onPause();
        threadCheckServerStatus.onPause();
    }

    /**
     * Stop everything. Time to go to bed
     */
    @Override
    protected void onStop()
    {
        super.onStop();
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
