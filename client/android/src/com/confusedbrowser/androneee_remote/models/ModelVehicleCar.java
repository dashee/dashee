package com.confusedbrowser.androneee_remote.models;

import android.util.Log;

import java.util.ArrayList;
import java.lang.Math;

import com.confusedbrowser.androneee_remote.RangeMapping;



/**
 * @author shahmirj is a cock
 *
 */
/**
 * @author shahmirj
 *
 */
public class ModelVehicleCar implements ModelVehicle 
{
    private float steer = 50.0f;
    private int prevSteer;
    
    private float power = 0.0f;
    private int prevPower;

    private int steerTrim = 0;
    private int powerTrim = 0;
    
    private float steerMax = 100.0f;
    private float steerMin = 0.0f;
    
    private float powerMax = 100.0f;
    private float powerMin = 0.0f;
    
    private boolean steerInverted = false;
    private boolean powerInverted = true;
    
    // Set up mappings
    private RangeMapping steerMapping;
    
    
    /*
     *  We can either use the phone pitch or an on screen slider
     *  to set the cars power. So setting that option as an enum.
     */
    private enum powerControls {
        PHONEPITCH, SLIDER 
    }
    
    private powerControls powerControl = powerControls.SLIDER;
    
    
    /*
     * Getter for steer
     * 
     * @returns steer
     */
    public float getSteer()
    {
    	return steer;
    }

    /*
     * Getter for power
     *
     * @returns power
     */
    public float getPower()
    {
    	return power;
    }


    /**
     * return the power of the car
     * interally this will be from 0 - 100 so need to compensate for min max and invert
     * @return float - the power value
     */
    private float getActualPower()
    {
        // 50 in case of power is stop
        float powerValue = 50.0f;

        if(this.power > this.powerMax){
            powerValue = this.powerMax;
        }else if (this.power < this.powerMin){
            powerValue = this.powerMin;
        }else{
            powerValue = this.power;
        }

        if(this.powerInverted)
            powerValue =  this.powerMax - powerValue + (100 - this.powerMax);

        return powerValue;
    }

    //public int get
	
    /**
     * Set up the car vehicle type
     */
    public ModelVehicleCar() 
    {
        this.prevSteer = (int)this.steer;
        this.prevPower = (int)this.power;
        steerMapping = new RangeMapping(-0.523f,0.523f,this.steerMax,this.steerMin);
    }

    /**
     * @see com.confusedbrowser.androneee_remote.models.ModelVehicle:getCommand()
     */
    @Override
    public ArrayList<byte[]> getCommands() 
    {
        // Commands are sent as 2 byte packets, the first byte, is the type
        // of command the second is the value.
        ArrayList<byte[]> commands = new ArrayList<byte[]>();

        int steerInt = Math.round(this.steer);
        int powerInt = Math.round(this.getActualPower());
        
        if(steerInt != this.prevSteer)
        {
            int sendSteer = steerInt+this.steerTrim;
            if (sendSteer > 100) { sendSteer = 100; }
            if (sendSteer < 0) { sendSteer = 0; }
            //Log.d("Dashee", "Steer Value: "+sendSteer);
            // Steering 17 converts to 00010001.
            commands.add(new byte[]{ 17, (byte)(sendSteer << 1) });
            this.prevSteer = steerInt;
        }
        
        if(powerInt != this.prevPower)
        {
            int sendPower = powerInt+this.powerTrim;
            if (sendPower > 100) { sendPower = 100; }
            if (sendPower < 0) { sendPower = 0; }

            // Steering 33 converts to 00100001.
            commands.add( new byte[]{ 33, (byte)(sendPower << 1) });
            this.prevPower = powerInt;
        }
        
        return commands;
    }

    /**
     * Set steer and power, given the phone's coordinates
     *
     * @param position - The phone position object
     */
    @Override
    public void setFromPhonePosition(ModelPhonePosition position) 
    {
        this.steer = this.getSteer(position.getRoll());
        if(powerControl == powerControls.PHONEPITCH)
        	this.power = this.getPowerFromPitch(position.getPitch());
    }
    
    
    /**
     * Set steer and power, given the phone's coordinates
     *
     * @param sliderPos - The phone position object
     */
    @Override
    public void setFromSlider(int sliderPos) 
    {
        if(powerControl == powerControls.SLIDER)
        	this.power = sliderPos;
    }
    
    /**
     * return the power of the phone given a pitch.
     * 
     * @see "http://shahmirj.com/blog/phone-tilt-notes-for-rc-car-acceleration"
     *
     * @param pitch - the pitch of the phone
     *
     * @return float - the power value
     */
    private float getPowerFromPitch(float pitch)
    {
    	// 50 in case of power is stop
    	float powerValue = 50.0f; 
    	
    	if(pitch >= -0.1f)
    		powerValue = 50.0f;
        else if(pitch >= -1.17f)
        	powerValue = RangeMapping.mapValue(pitch,-1.17f,-0.5f,50.0f,this.powerMax); // TODO: invert option
        else if(pitch <=-1.70f) 
        	powerValue = RangeMapping.mapValue(pitch, -2.1f, -1.70f, this.powerMin, 50.0f);

        Log.d("Dashee", "Power Inverterd: " + this.powerInverted);

        if(this.powerInverted)
    		powerValue =  this.powerMax - powerValue + (100 - this.powerMax);
    	
    	return powerValue;
    }


    /**
     * Return the steer value, given the roll of the phone.
     * Steer being 50 is centre, 0 is full left and 100 is full right
     *
     * @param roll - the roll value in radians
     *
     * @return float - the steer value
     */
    private float getSteer(float roll) 
    {
    	float steerValue = steerMapping.remapValue(roll);
    	if(this.steerInverted)
    		steerValue =  this.steerMax - steerValue;
    	return steerValue;
    }

	@Override
	public void setTrim(int channel, int value)
	{
		switch(channel){
			case 1:
				this.steerTrim = value;
				break;
			case 2:
				this.powerTrim = value;
				break;
			default:
				break;
		}
	}
	
	@Override
	public void setMax(int channel, float value)
	{
		switch(channel){
			case 1:
				this.steerMax = value;
				steerMapping.updateTargets(this.steerMin, this.steerMax);
				break;
			case 2:
				this.powerMax = value;
				break;
			default:
				break;
		}
	}
	
	
	@Override
	public void setMin(int channel, float value)
	{
		switch(channel){
			case 1:
				this.steerMin = value;
				steerMapping.updateTargets(this.steerMin, this.steerMax);
				break;
			case 2:
				this.powerMin = value;
				break;
			default:
				break;
		}
	}
	
	
	@Override
	public void setInvert(int channel, boolean value)
	{
		switch(channel){
			case 1:
				this.steerInverted = value;
				break;
			case 2:
				this.powerInverted = value;
				break;
			default:
				break;
		}
	}
	
}
