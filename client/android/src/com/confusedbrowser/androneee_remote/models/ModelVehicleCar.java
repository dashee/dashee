package com.confusedbrowser.androneee_remote.models;

import android.util.Log;

import java.util.ArrayList;
import java.lang.Math;
import java.util.List;

import com.confusedbrowser.androneee_remote.Exceptions.InvalidValue;
import com.confusedbrowser.androneee_remote.RangeMapping;

/**
 * @author shahmirj is a cock
 */

/**
 * @author shahmirj
 */
public class ModelVehicleCar implements ModelVehicle 
{

    public static final float START_RANGE = 0.0f;
    public static final float MID_RANGE = 128.0f;
    public static final float END_RANGE = 255.0f;

    /**
     * The set of variables which hold steering information
     */
    private float steer = MID_RANGE; // Between 0 - 100
    private float adjustedSteer = MID_RANGE;
    private int steerTrim = 0;
    private float steerMin = START_RANGE;
    private float steerMax = END_RANGE;
    private boolean steerInverted = false;

    float tempPower;

    /**
     * Set of variables which hold power information
     */
    private float power = MID_RANGE; // Between 0 - 100
    private float adjustedPower;
    private int powerTrim = 0;
    private float powerMax = END_RANGE;
    private float powerMin = START_RANGE;
    private boolean powerInverted = true;

    /**
     * Define the gap when the values are resent. We want
     * to ensure that the client communicates with the
     * server in a regular basis, so the server can know
     * the client is still alive. Change this value to determine
     * the milliseconds the client should talk to the server if
     * no new commands are being sent
     */
    private int timeOut = 17;

    /**
     * Hold the last time value of the command sent. This will help
     * us determine the last time the value was sent, we can use this
     * for comparison before we can send another value.
     */
    private long timeValueSent = 0; // Time when last value was set

    // Commands are sent as 2 byte packets, the first byte, is the type
    // of command the second is the value.
    List<Byte> commands = new ArrayList<Byte>();

    /**
     * When things like steerMax and and steerMin
     * Change want temp flag so UI can update efficiently instead of all the time
     */
    private boolean settingsChanged = false;



    /**
     * The mapping objects for turning degrees into steer values
     */
    private RangeMapping adjustedSteerMapping;
    private RangeMapping visualSteerMapping;
    
    /**
     * We can either use the phone pitch or an on screen slider
     * to set the cars power. So setting that option as a boolean
     */
    /*private enum powerControls {
        PHONEPITCH, SLIDER 
    }*/

    /**
     * This will change the power to use pitch or the touch
     */
    private boolean powerControlSlider = true;

    /**
     * Set up the car vehicle type
     */
    public ModelVehicleCar()
    {
        this.adjustedSteerMapping = new RangeMapping(-0.5f,0.5f,this.steerMax,this.steerMin);
        this.visualSteerMapping = new RangeMapping(-0.5f,0.5f,100.0f,0.0f);
    }

    /**
     * @see com.confusedbrowser.androneee_remote.models.ModelVehicle:getCommand()
     *
     * @return ArrayList<byte> - A list of bytes which form the command to be sent to the server
     */
    @Override
    public List<Byte> getCommands()
    {
        long currentTime = System.currentTimeMillis();
        boolean timeToSend = (currentTime-this.timeValueSent > this.timeOut);

        commands.clear();

        if(timeToSend)
        {
            commands.add((byte)0);
            commands.add((byte)(Math.round(this.adjustedSteer)));
            commands.add((byte)(Math.round(this.adjustedPower)));
        }

        if(!commands.isEmpty())
            this.timeValueSent = System.currentTimeMillis();

        return commands;
    }

    /**
     * Getter for steer
     * 
     * @return float - The current steer value
     */
    public float getSteer()
    {
    	return this.steer;
    }

    /**
     * Get the max steer value
     *
     * @return float - The max steer value
     */
    public float getSteerMax()
    {
        return this.steerMax;
    }

    /**
     * Get the min steer value
     *
     * @return float - The min steer value
     */
    public float getSteerMin()
    {
        return this.steerMin;
    }

    /**
     * Getter for power
     *
     * @return float - The current power value
     */
    public float getPower()
    {
        return this.power;
    }
    /**
     * Get the max power value
     *
     * @return float - The max power value
     */
    public float getPowerMax()
    {
        return this.powerMax;
    }

    /**
     * Get the min power value
     *
     * @return float - The min power value
     */
    public float getPowerMin()
    {
        return this.powerMin;
    }

    /**
     * Flag to check if some settings have changed to allow UI updates
     *
     * @return boolean - settingChanged value
     */
    public boolean getSettingChange()
    {
        boolean curValue = this.settingsChanged;
        this.settingsChanged = false;
        return curValue;
    }

    /**
     * Apply any constrains from settings such as max, min and trim.
     */
    private void setAdjustedPower()
    {
        // Going from 50 - 100 is forward apply forward this.powerMax
        if(this.power >= MID_RANGE)
            tempPower = RangeMapping.mapValue(this.power, MID_RANGE, END_RANGE, MID_RANGE, this.powerMax);
        else{
            // Going from 0 - 50 is reverse apply this.powerMin
            tempPower = RangeMapping.mapValue(this.power, START_RANGE, MID_RANGE, this.powerMin, MID_RANGE);
        }

        if(this.powerInverted)
            tempPower =  END_RANGE - tempPower;

        this.adjustedPower = tempPower;

        // Apply trim
        this.adjustedPower = Math.max(this.powerMin, Math.min(this.powerMax, this.adjustedPower+this.powerTrim));
    }

    /**
     * Set adjusted steer from phone roll.
     * Apply any constrains from settings such as max, min and trim.
     *
     * @param roll - the roll value in radians
     *
     */
    private void setAdjustedSteerFromRoll(float roll)
    {
        this.adjustedSteer = adjustedSteerMapping.remapValue(roll);
        if(this.steerInverted)
            this.adjustedSteer =  this.steerMax - this.adjustedSteer;
        // Apply trim
        this.adjustedSteer = Math.max(this.steerMin, Math.min(this.steerMax, this.adjustedSteer+this.steerTrim));
    }

    /**
     * Set steer and power, given the phone's coordinates
     *
     * @param position - The phone position object
     */
    @Override
    public void setFromPhonePosition(ModelPhonePosition position) 
    {
        this.steer = visualSteerMapping.remapValue(position.getRoll());

        this.setAdjustedSteerFromRoll(position.getRoll());

        if(!powerControlSlider)
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
        if(powerControlSlider){
        	this.power = sliderPos;
            this.setAdjustedPower();
        }
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
    	float powerValue = MID_RANGE;
    	
    	if(pitch >= -0.1f)
    		powerValue = MID_RANGE;
        else if(pitch >= -1.17f)
        	powerValue = RangeMapping.mapValue(pitch,-1.17f,-0.5f,MID_RANGE, END_RANGE);
        else if(pitch <=-1.70f) 
        	powerValue = RangeMapping.mapValue(pitch, -2.1f, -1.70f, START_RANGE, MID_RANGE);
    	
    	return powerValue;
    }

    /**
     * Sets the Trim value
     *
     * @param channel - Desired channel number.
     * @param value - Desired trim value.
     */
	@Override
	public void setTrim(int channel, int value)
	{
        settingsChanged = true;
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

    /**
     * This will set the steer max, or power max according to the channel
     * value.
     *
     * @param channel - Desired channel number.
     * @param value - The max value of the channel.
     *
     * @throws java.lang.RuntimeException - If max is invalid
     */
	@Override
	public void setMax(int channel, float value)
	{
        // TODO: Create a custom exception
        if (value < 0 || value > 255)
            throw new InvalidValue("Value of Max must be from 0-255.");

        settingsChanged = true;

		switch(channel){
			case 1:
                // TODO: Use a custom Exception
                if (value <= this.steerMin)
                    throw new InvalidValue("The Max value must be greater than Min.");

				this.steerMax = value;
				this.adjustedSteerMapping.updateTargets(this.steerMax, this.steerMin);
				break;

			case 2:

                // TODO: Use a custom Exception
                if (value <= this.powerMin)
                    throw new InvalidValue("The Max value must be greater than Min.");

				this.powerMax = value;
				break;

			default:
				break;
		}
	}

    /**
     * This will set the steer min, or power min according to the channel
     * value.
     *
     * @param channel - Desired channel number.
     * @param value - The max value of the channel.
     *
     * @throws java.lang.RuntimeException - If min is invalid
     */
	@Override
	public void setMin(int channel, float value)
	{
        // TODO: Create a custom exception
        if (value < 0 || value > 255)
            throw new InvalidValue("Value of Max must be from 0-255");

        settingsChanged = true;

		switch(channel){
			case 1:

                // TODO: Use a custom Exception
                if (value > this.steerMax)
                    throw new InvalidValue("The Min value must not be greater than Max.");

				this.steerMin = value;
                this.adjustedSteerMapping.updateTargets(this.steerMax, this.steerMin);
				break;

			case 2:

                // TODO: Use a custom Exception
                if (value >= this.powerMax)
                    throw new InvalidValue("The Min value must not be greater than Max.");

				this.powerMin = value;
				break;

			default:
				break;
		}
	}

    /**
     * Set the invert variable
     *
     * @param channel - Desired channel number.
     * @param value - Desired invert as a boolean.
     */
	@Override
	public void setInvert(int channel, boolean value)
	{
        settingsChanged = true;

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

    /**
     * Sets if we are using the screen as a slider or not
     *
     * @param value - The enable value
     */
    @Override
    public void setPowerToUsePitch(boolean value)
    {
        this.powerControlSlider = !value;
    }


    /**
     * Stabilize car on activity resume, i.e. make sure there
     * is no throttle applied.
     */
    @Override
    public void onResume()
    {
        this.power = MID_RANGE;
    }
}
