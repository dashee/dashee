package com.confusedbrowser.androneee_remote.fragments;

import android.support.v4.app.Fragment;

import com.confusedbrowser.androneee_remote.models.*;

/**
 * FragmentHud abstract class. Create the functions
 * that mainActivity can refer to without using this class
 *
 * @author David Buttar
 * @author Shahmir Javaid
 */
public abstract class FragmentHud extends Fragment
{
    public FragmentHud()
    {
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
    
    /**
     * Set the IP of HUD
     *
     * @param ip - The IP Address
     */
    public abstract void setHudIp(String ip);

    /**
     * Set the Bytes per second.
     *
     * @param bps - The Bytes per seconds
     */
    public abstract void setHudBps(int bps);

    /**
     * Set the Connection Status
     *
     * @param connection - The Connection string
     */
    public abstract void setHudConnection(String connection);

    /**
     * Set the Position of the hud
     *
     * @param v - The vehicle object
     */
    public abstract void setPosition(ModelVehicle vehicle);

    /**
     * Assign a reference of vehicle model to the hud
     *
     * @param v - The vehicle object
     */
	public abstract void setVehicle(ModelVehicle modelVehicle);
}
