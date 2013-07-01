package com.confusedbrowser.androneee_remote.fragments;

import java.text.DecimalFormat;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.LayoutInflater;
import android.view.ViewGroup;
import android.view.View;
import android.content.SharedPreferences;
import android.widget.LinearLayout;
import com.confusedbrowser.androneee_remote.DrawHud;
import com.confusedbrowser.androneee_remote.R;
import com.confusedbrowser.androneee_remote.models.*;

import android.widget.TextView;

/**
 * This is our HUD Fragment. which controls, sending and receiving controls
 * from our servers, and updating our HUD
 * 
 * @author David Buttar
 * @author Shahmir Javaid
 */
public class FragmentHudCar extends FragmentHud
{
    /**
     * This is the variable where our HUD is drawn
     * We use DrawHud 
     */
    LinearLayout layout_hud;
    
    /**
     * Draw our Hud object
     */
    DrawHud draw_hud;
            
    /**
     * Handle to our TextViews
     */    
    private TextView textViewHudIpValue;
    private TextView textViewHudConnectionValue;
    private TextView textViewHudBpsValue; //Bytes Per Second
    private TextView textViewHudPitchValue; //Pitch Value
    private TextView textViewHudRollValue; //Pitch Value
    
    /**
     * Constructor. Required by Fragment type Objects,
     * and they have to be public
     */
    public FragmentHudCar()
    {
    }
    
    /**
     * Set our HUD. Initiate the servers IP address so our thread can talk to it, 
     * start our thread and return the view which is required by this function
     */
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) 
    {
        View view = inflater.inflate(R.layout.fragment_hud, container, false);

        layout_hud = (LinearLayout)view.findViewById(R.id.hud_canvas);
        draw_hud = new DrawHud (this.getActivity());
        layout_hud.addView(draw_hud);
        
        //SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this.getActivity());

        // Set all of our textViews        
        textViewHudIpValue = (TextView)view.findViewById(R.id.hud_text_ip_value);
        textViewHudConnectionValue = (TextView)view.findViewById(R.id.hud_text_connection_value);
        textViewHudBpsValue = (TextView)view.findViewById(R.id.hud_text_bps_value);
        textViewHudPitchValue = (TextView)view.findViewById(R.id.hud_text_pitch_value);
        textViewHudRollValue = (TextView)view.findViewById(R.id.hud_text_roll_value);

        this.setHudIp("None");
        this.setHudConnection("unknown");
        this.setHudBps(0);
        this.setHudPitch(0.0f);
        this.setHudRoll(0.0f);
        
        return view;
    }
    
    /**
     * Set our textbox ip value
     *
     * @param value - the ip address
     */
    public void setHudIp(String ip)
    {
        textViewHudIpValue.setText(ip);
    }
    
    /**
     * Set our textbox connection value
     *
     * @param value - the ip address
     */
    public void setHudConnection(String ip)
    {
        textViewHudConnectionValue.setText(ip);
    }
    
    /**
     * Set our textbox BytesPerSecond value
     *
     * @param bps - the bps value
     */
    public void setHudBps(int bps)
    {
        if (bps < 0)
            textViewHudBpsValue.setText("Negative?");

        textViewHudBpsValue.setText(Integer.toString(bps));
    }
    
    /**
     * Set our textbox Pitch value
     *
     * @param pitch - the pitch value
     */
    public void setHudPitch(float pitch)
    {
        if (pitch < 0.0)
            textViewHudPitchValue.setText("Negative?");
        
        DecimalFormat twoDecimal = new DecimalFormat("000.00");
        textViewHudPitchValue.setText(twoDecimal.format(pitch));
    }
    
    /**
     * Set our textbox Roll value
     *
     * @param roll - the pitch value
     */
    public void setHudRoll(float roll)
    {
        if (roll < 0.0)
            textViewHudRollValue.setText("Negative?");
    
        DecimalFormat twoDecimal = new DecimalFormat("000.00");
        textViewHudRollValue.setText(twoDecimal.format(roll));
    }
    
    /**
     * Rotate our HUD. Given a value, rotate our hud accordingly
     *
     * @param roll - The rotation value.
     */
    public void rotateHud(float roll)
    {
        layout_hud.setRotation(-1.0f*(roll - 50.0f));
    }
    
    /**
     * Change our Hud, according to the vehicle.
     * The vehicle must be a ModelVehicleCar, other
     * wise an exception will be thrown.
     *
     * @param car - The vehicle
     * @throws Exception - If vehicle is not ModelVehicleCar
     */
    public void setPosition(ModelVehicle vehicle)
    {
        if (vehicle instanceof ModelVehicleCar)
        {
            ModelVehicleCar car = (ModelVehicleCar)vehicle;
            this.setHudRoll(car.getSteer());
            this.setHudPitch(car.getPower());
            this.rotateHud(car.getSteer());
        }
        else
        {
            //throw new Exception("vehicle must be a ModelVehicleCar");
        }
    }
}
