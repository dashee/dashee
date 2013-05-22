package com.confusedbrowser.androneee_remote.fragment;

import java.util.Observable;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.LayoutInflater;
import android.view.ViewGroup;
import android.view.View;
import android.content.SharedPreferences;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.widget.LinearLayout;
import com.confusedbrowser.androneee_remote.DrawHud;
import com.confusedbrowser.androneee_remote.PhonePosition;
import com.confusedbrowser.androneee_remote.R;
import com.confusedbrowser.androneee_remote.SendControlsThread;

/**
 * This is our HUD Fragment, which controls, sending and receiving controls
 * from our servers, and updating our HUD
 * 
 * @author David Buttar
 * @author Shahmir Javaid
 */
public class HudFragment extends Fragment {
	
	/**
	 * This is the variable where our HUD is drawn
	 * We use DrawHud 
	 */
	LinearLayout layout_hud;
	
	DrawHud draw_hud;
	
	/**
	 * This is our thread_servo, which allows us to communicate
	 * with our server on the RC robot, this thread handles the
	 * network communication
	 */
	SendControlsThread thread_servo;
	
	/**
	 * This is the ip_address which is set using the preferences
	 * It can be updated by the user, using the preferences variable
	 */
	String ip_address;
	
	/**
	 * This will map our values, into the correct required coordinates
	 * 
	 * @param (float)value
	 * @param (double)leftMin
	 * @param (double)leftMax
	 * @param (double)rightMin
	 * @param (double)rightMax
	 * @return - The double value of the position from 0-100
	 */
    protected double mapping(float value, double leftMin, double leftMax, double rightMin, double rightMax){
		
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
	
    public HudFragment()
    {
        
    }
    
    /**
     * Set our HUD, Initiate the servers IP address so our thread can talk to it, start our thread
     * and return the view which is required by this function
     */
	public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {

		View view = inflater.inflate(R.layout.fragment_hud, container, false);

		layout_hud = (LinearLayout)view.findViewById(R.id.canvas);
		draw_hud = new DrawHud (this.getActivity());
        layout_hud.addView(draw_hud);
             
        SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this.getActivity());
        ip_address = prefs.getString("pref_ip", "192.168.0.11");
        Log.d("androneee", "ip is: " + ip_address);
        
        // Create threads for send and receiving data from the vehicle  
        thread_servo = new SendControlsThread(this.getActivity(), ip_address, 2047, 50);
        thread_servo.start();
        		
		return view;
    }
	
	/**
	 * Pause our thread
	 */
	public void onPause()
	{
		super.onPause();
		thread_servo.onPause();
	}
	
	/**
	 * Resume our thread
	 */
	public void onResume()
	{
		super.onResume();
		thread_servo.onResume();
	}

	/**
	 * This function updates our HUD, and sends the server
	 * the update location, using our thread. To achieve this
	 * it uses the phones, Observable object
	 * 
	 * @param o
	 * @param arg
	 */
	public void update(Observable o, Object arg) 
	{
        PhonePosition pp = (PhonePosition) o;
        int progress = (int)mapping(-pp.roll_val,-0.523,0.523,0,100);
        
        thread_servo.setPosition(progress);
        layout_hud.setRotation(-1*(progress - 50));
	}
	
}