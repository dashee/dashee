package com.confusedbrowser.androneee_remote.fragments;

import java.text.DecimalFormat;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View.OnTouchListener;
import android.view.ViewGroup;
import android.view.View;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Typeface;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.SeekBar;
import com.confusedbrowser.androneee_remote.DrawHud;
import com.confusedbrowser.androneee_remote.R;
import com.confusedbrowser.androneee_remote.RangeMapping;
import com.confusedbrowser.androneee_remote.models.*;
import android.text.Html;

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
    
    /*
     * Hud Slider to control power
     */
    SeekBar mSeekBar;
    
    View view;
    
    /*
     * Assign area for current steer value
     */
    float steer;
            
    /**
     * Handle to our TextViews
     */    
    private TextView textViewHudIpValue;
    private TextView textViewHudConnectionValue;
    private TextView textViewHudBpsValue; //Bytes Per Second
    private TextView textViewHudPitchValue; //Pitch Value
    private TextView textViewHudRollValue; //Pitch Value
    private TextView textViewHudRollMinValue; //Pitch Min Value
    private TextView textViewHudRollMaxValue; //Pitch Max Value
    private TextView textViewHudPowerMinValue;
    private TextView textViewHudPowerMaxValue;

    private ModelVehicleCar car; //Pitch Value
    


    /**
     * Constructor. Required by Fragment type Objects,
     * and they have to be public
     */
    public FragmentHudCar()
    {
    }
    
    public void setVehicle(ModelVehicle modelVehicle)
    {
    	this.car = (ModelVehicleCar) modelVehicle;
    }
    
    private void setVehiclePower(int power)
    {
    	this.car.setFromSlider(power);
    }
    
    /**
     * Set our HUD. Initiate the servers IP address so our thread can talk to it, 
     * start our thread and return the view which is required by this function
     */
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) 
    {
        view = inflater.inflate(R.layout.fragment_hud, container, false);
        layout_hud = (LinearLayout)view.findViewById(R.id.hud_canvas);
        draw_hud = new DrawHud (this.getActivity());
        layout_hud.addView(draw_hud);
        
        /*LinearLayout slider_layout = (LinearLayout)view.findViewById(R.id.hud_power_slider);
        slider_layout.setRotation(-90.0f);*/
        
        // Use the height and width of the image and the position of the stick to
        // map to car power value
        final ImageView iv = (ImageView)view.findViewById(R.id.power_stick);
        iv.setOnTouchListener(new OnTouchListener(){
			@Override
			public boolean onTouch(View v, MotionEvent event) {
				//Log.d("dashee", "Got click");
				float mapVal = RangeMapping.mapValue(event.getY(), 120, iv.getHeight()-72, 100, 50);
				setVehiclePower((int) mapVal);
				//moveGrip((int) Math.round(event.getX()),(int) Math.round(event.getY()));
				if (event.getAction() == MotionEvent.ACTION_UP) {
					//moveGrip(150,150);
					setVehiclePower(50);
				}
				return true;
			}
		});

        Button optsButton = (Button)view.findViewById(R.id.dot_settings);
        optsButton.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
            	
                Intent intent = new Intent(getActivity(), com.confusedbrowser.androneee_remote.preferences.PreferencesActivity.class);
                startActivity(intent);
            }
        });

        //SharedPreferences prefs = PreferenceManager.getDefaultSharedPreferences(this.getActivity());
        Typeface visitorFont = Typeface.createFromAsset(getActivity().getAssets(),"fonts/visitor1.ttf");
        Typeface novamonoFont = Typeface.createFromAsset(getActivity().getAssets(),"fonts/novamono2.ttf");

        // Set all of our textViews        
        textViewHudIpValue = (TextView)view.findViewById(R.id.hud_text_ip_value);
        textViewHudConnectionValue = (TextView)view.findViewById(R.id.hud_text_connection_value);
        textViewHudBpsValue = (TextView)view.findViewById(R.id.hud_text_bps_value);

        textViewHudPitchValue = (TextView)view.findViewById(R.id.hud_text_pitch_value);
        textViewHudPitchValue.setTypeface(novamonoFont);
        textViewHudPitchValue.getPaint().setAntiAlias(false);

        textViewHudRollValue = (TextView)view.findViewById(R.id.hud_text_roll_value);
        textViewHudRollValue.setTypeface(novamonoFont);
        textViewHudRollValue.getPaint().setAntiAlias(false);

        textViewHudRollMinValue = (TextView)view.findViewById(R.id.hud_text_roll_min_value);
        textViewHudRollMinValue.setTypeface(novamonoFont);
        textViewHudRollMinValue.getPaint().setAntiAlias(false);

        textViewHudRollMaxValue = (TextView)view.findViewById(R.id.hud_text_roll_max_value);

        textViewHudPowerMaxValue = (TextView)view.findViewById(R.id.hud_text_pitch_max_value);
        textViewHudPowerMinValue = (TextView)view.findViewById(R.id.hud_text_pitch_min_value);

        this.setElementsFont(R.id.hud_text_roll_max_value, novamonoFont);
        this.setElementsFont(R.id.hud_text_ip_value, visitorFont);
        this.setElementsFont(R.id.hud_text_connection_value, visitorFont);
        this.setElementsFont(R.id.hud_text_power_label, visitorFont);
        this.setElementsFont(R.id.hud_text_pitch_min_value, novamonoFont);
        this.setElementsFont(R.id.hud_text_pitch_max_value, novamonoFont);
        this.setElementsFont(R.id.hud_text_tilt_label, visitorFont);
        
        this.setHudConnection("unknown");
        //this.setHudBps(0);
        this.setHudPitch(50.0f);
        this.setHudRoll(50.0f);
        
        // Get the sharedPreferences so the values can be set
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this.getActivity());
        this.setHudIp(sharedPreferences.getString("pref_server_ip", "192.168.1.115"));
        
        return view;
    }

    /*
     * Sets the ids listed to the font listed
     */
    private void setElementsFont(int elementID, Typeface font){
        TextView textElement = (TextView)view.findViewById(elementID);
        textElement.setTypeface(font);
        textElement.getPaint().setAntiAlias(false);
    }
    
    /**
     * Set our textbox ip value
     *
     * @param ip - the ip address
     */
    public void setHudIp(String ip)
    {
        textViewHudIpValue.setText(ip);
    }
    
    /**
     * Set our textbox connection value
     *
     * @param ip - the ip address
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
        //Display invalid values when things are out of range
        if (pitch < 0.0f || pitch > 100.0f)
            textViewHudPitchValue.setText(Html.fromHtml("<font color='#D93600'>---</font>"));

        int pitchValue = Math.round(pitch);
        textViewHudPitchValue.setText(""+pitchValue);

        // This slows shit up, No idea why, investigate. because having this would be good
        /*
        if (pitchValue == 100)
            textViewHudPitchValue.setText(Html.fromHtml("<font color='#D93600'>100</font>"));
        else if (pitchValue == 0)
            textViewHudPitchValue.setText(Html.fromHtml("<font color='#D93600'>000</font>"));
        else if (pitchValue < 10)
            textViewHudPitchValue.setText(Html.fromHtml("<font color='#333333'>00</font>"+pitchValue));
        else
            textViewHudPitchValue.setText(Html.fromHtml("<font color='#333333'>0</font>"+pitchValue));
        */
    }



    /**
     * Set our textbox Pitch value
     *
     * @param car - the car model
     */
    public void setMaxMinValues(ModelVehicleCar car)
    {
        if(car.getSettingChange()){
            Log.d("Dashee", "Updating minor settings");
            String steerMin = String.format("%03d", Math.round(car.getSteerMin()));
            String steerMax = String.format("%03d", Math.round(car.getSteerMax()));
            String powerMin = String.format("%03d", Math.round(car.getPowerMin()));
            String powerMax = String.format("%03d", Math.round(car.getPowerMax()));
            textViewHudRollMinValue.setText(steerMin+"");
            textViewHudRollMaxValue.setText(steerMax+"");

            textViewHudPowerMinValue.setText(powerMin+"");
            textViewHudPowerMaxValue.setText(powerMax+"");
        }
    }

    
    /**
     * Set our textbox Roll value
     *
     * @param roll - the pitch value
     */
    public void setHudRoll(float roll)
    {
        //Display invalid values when things are out of range
        if (roll < 0.0f || roll > 100.0f)
            textViewHudRollValue.setText(Html.fromHtml("<font color='#D93600'>---</font>"));

        int rollValue = Math.round(roll);

        textViewHudRollValue.setText(rollValue+"");

        /*if (rollValue == 100)
            textViewHudRollValue.setText(Html.fromHtml("<font color='#D93600'>100</font>"));
        else if (rollValue == 0)
            textViewHudRollValue.setText(Html.fromHtml("<font color='#D93600'>000</font>"));
        else if (rollValue < 10)
            textViewHudRollValue.setText(Html.fromHtml("<font color='#333333'>00</font>"+rollValue));
        else
            textViewHudRollValue.setText(Html.fromHtml("<font color='#333333'>0</font>"+rollValue));*/
    }
    
    /**
     * Rotate our HUD. Given a value, rotate our hud accordingly
     *
     * @param roll - The rotation value.
     */
    public void rotateHud(float roll)
    {
        //layout_hud.setRotation(-1.0f*(roll - 50.0f));
    	draw_hud.setTilt(roll);
    }
    
    /**
     * Change our Hud, according to the vehicle.
     * The vehicle must be a ModelVehicleCar, other
     * wise an exception will be thrown.
     *
     * @param vehicle - The vehicle
     *
     * @throws Exception - If vehicle is not ModelVehicleCar
     */
    public void setPosition(ModelVehicle vehicle)
    {
        if (vehicle instanceof ModelVehicleCar)
        {
            ModelVehicleCar car = (ModelVehicleCar)vehicle;
            this.steer = car.getSteer();
            this.setHudRoll(this.steer);
            this.setHudPitch(car.getPower());
            this.rotateHud(this.steer);
            this.setMaxMinValues(car);
            draw_hud.setPowerPerc((car.getPower()-50)/50);
        }
        else
        {
            //throw new Exception("vehicle must be a ModelVehicleCar");
        }
    }
}
