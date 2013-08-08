package com.confusedbrowser.androneee_remote;

import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.OnSharedPreferenceChangeListener;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentTransaction;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.WindowManager;
import android.widget.SeekBar;
import java.util.Observable;
import java.util.Observer;

import com.confusedbrowser.androneee_remote.fragments.*;
import com.confusedbrowser.androneee_remote.models.*;
import com.confusedbrowser.androneee_remote.threads.*;

/**
 * The main activity that the program will run.
 * This will set our fragments, handle our preferences
 * changing, start the threads which communicate to our servers
 * set and listen to the Observers so actions can be taken when things are changed
 *
 * @author David Buttar
 * @author Shahmir Javaid
 */
public class MainActivity 
    extends FragmentActivity 
    implements SeekBar.OnSeekBarChangeListener, Observer, OnSharedPreferenceChangeListener
{

    /**
     * Create instances of our fragments in memory.
     * So they don't have to be initialised every time, and hold
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
     * This will poll our server to check weather it is still
     * alive or not. If not then an observer will be notified
     * It is this observer that will handle other threads, which require
     * this server
     */
    public ThreadCheckServerStatus threadCheckServerStatus;
    
    /**
     * Handle to our Phone schematics. This will return
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
     * SharedPrefrences object for registering
     */
    private SharedPreferences sharedPreferences;

    @Override
    protected void onCreate(Bundle savedInstanceState) 
    {
        super.onCreate(savedInstanceState);
        
        // Keep our screen constantly on
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        
        // Set the XML view for this activity
        setContentView(R.layout.activity_main);
        
        // However, if we're being restored from a previous state,
        // then we don't need to do anything and should return or else
        // we could end up with overlapping fragments.
        /*if (savedInstanceState != null) {
            return;
        }*/
        
        this.sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        this.sharedPreferences.registerOnSharedPreferenceChangeListener(this);

        // This will initialise our PhonePosition Observer,
        // So our this.update function can handle updates 
        this.modelPosition = new ModelPhonePosition(getBaseContext());
        this.modelPosition.addObserver(this);
        
        //Create our ServerState model
        this.modelServerState = new ModelServerState(this.sharedPreferences.getString("pref_server_ip", "192.168.114"));
        this.modelServerState.addObserver(this);
        
        // Create our vehicle model
        this.modelVehicle = new ModelVehicleCar();
        
    	// Create our fragment views
        this.fragmentHud = new FragmentHudCar();
        this.fragmentHud.setVehicle(this.modelVehicle);
        this.fragmentLog = new FragmentLog();
    	
        //Set the initial view to our HUD
        FragmentTransaction ft = getSupportFragmentManager().beginTransaction();
        ft.replace(R.id.fragment_content, this.fragmentHud);
        ft.commit();

    	
        
        
        // Initialise our thread
        this.threadPassPositionControls = new ThreadPassPositionControls(this.modelServerState, this.modelVehicle);
        this.threadPassPositionControls.start();

        // Initialise our thread
        this.threadCheckServerStatus = new ThreadCheckServerStatus(this.modelServerState);
        this.threadCheckServerStatus.start();

    }
    
    /**
     * Create a listener to activate when SharedPreferences are changed.
     *
     * @param pref - The SharedPreferences
     * @param key - The key value changed
     */
    public void onSharedPreferenceChanged(SharedPreferences prefs, String key) 
    {
    	if(key.equals("pref_server_ip")){
    		Log.d("Dashee", "Setting new ip addess: "+prefs.getString("pref_server_ip", "192.168.114"));
    		this.modelServerState.setIp(prefs.getString("pref_server_ip", "192.168.114"));
    	}else if(key.equals("pref_server_port")){
    		this.modelServerState.setControlsPort(Integer.parseInt(prefs.getString("pref_server_port", "2047")));
    	}else if(key.contains("pref_channel")){
    		//e.g. pref_channel01
    		Log.d("Dashee", "Channel Requested: "+key);
    		Log.d("Dashee", "Channel Requested: "+key.substring(13, 14));
    		int channel =  Integer.parseInt(key.substring(13, 14));
    		
    		if(key.contains("invert")){
    			this.modelVehicle.setInvert(channel, prefs.getBoolean(key, false));
    		}else if(key.contains("max")){
    			this.modelVehicle.setMax(channel, Integer.parseInt(prefs.getString(key, "100")));
    		}else if(key.contains("min")){
    			this.modelVehicle.setMin(channel, Float.parseFloat(prefs.getString(key, "0")));
    		}else{
    			this.modelVehicle.setTrim(channel, Integer.parseInt(prefs.getString(key, "0")));
    		}
    	}
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
                Intent preferencesActivity = new Intent(getBaseContext(), com.confusedbrowser.androneee_remote.preferences.PreferencesActivity.class);
                startActivity(preferencesActivity);
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
        try
        {
            if (o instanceof ModelPhonePosition)
            {
                ModelPhonePosition position = (ModelPhonePosition)o;
                this.modelVehicle.setFromPhonePosition(position);
                fragmentHud.setPosition((ModelVehicleCar) this.modelVehicle);
                //fragmentHud.setHudConnection(position.getRoll()+"");
            }
            else if (o instanceof ModelServerState)
            {
                switch ((ModelServerState.Notifier)arg)
                {
                    case STATUS_CONTROLS:
                    case STATUS_TELEMETRY:
                    case STATUS_FPV:
                        if (this.modelServerState.isAlive())
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
                        break;
                    
                    case IP:
                        runOnUiThread(new Runnable() {
                            public void run()
                            {
                                fragmentHud.setHudIp(modelServerState.getIp().getHostAddress()); 
                            }
                        });
                        break;
				default:
					break;
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
        this.modelPosition.onResume();
        this.threadPassPositionControls.onResume();
        this.threadCheckServerStatus.onResume();
    }
    
    /**
     * App is paused, handle pause systems.
     * Pause the thread, and stop the PhoneRoll monitoring
     */
    @Override
    protected void onPause() 
    {
        super.onPause();
        this.modelPosition.onPause();
        this.threadPassPositionControls.onPause();
        this.threadCheckServerStatus.onPause();
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
