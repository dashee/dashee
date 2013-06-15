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

/**
 * This is our HUD Fragment. which controls, sending and receiving controls
 * from our servers, and updating our HUD
 * 
 * @author David Buttar
 * @author Shahmir Javaid
 */
public class HudFragment extends Fragment
{
    /**
     * This is the variable where our HUD is drawn
     * We use DrawHud 
     */
    LinearLayout layout_hud;
    
    DrawHud draw_hud;
	
    public HudFragment()
    {
    }
    
    /**
     * Set our HUD. Initiate the servers IP address so our thread can talk to it, 
     * start our thread and return the view which is required by this function
     */
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) 
    {
        View view = inflater.inflate(R.layout.fragment_hud, container, false);

        layout_hud = (LinearLayout)view.findViewById(R.id.canvas);
        draw_hud = new DrawHud (this.getActivity());
        layout_hud.addView(draw_hud);
        
        return view;
    }

    /**
     * Pause our thread
     */
    public void onPause()
    {
        super.onPause();
    }
    
    /**
     * Resume our thread
     */
    public void onResume()
    {
        super.onResume();
    }

    public void rotateHud(float progress)
    {
        layout_hud.setRotation(-1.0f*(progress - 50.0f));
    }
}
