package com.confusedbrowser.androneee_remote.models;

import java.util.ArrayList;
import java.lang.Math;

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
    /**
     * The set of variables which hold steering information
     */
    private float steer = 50.0f; // Between 0 - 100
    private float actualSteer = 50.0f;
    private int prevSteer;
    private int steerTrim = 0;
    private float steerMax = 100.0f;
    private float steerMin = 0.0f;
    private boolean steerInverted = false;

    /**
     * Set of variables which hold power information
     */
    private float power = 50.0f; // Between 0 - 100
    private int prevPower;
    private int powerTrim = 0;
    private float powerMax = 100.0f;
    private float powerMin = 0.0f;
    private boolean powerInverted = true;

    /**
     * Define the gap when the values are resent. We want
     * to ensure that the client communicates with the
     * server in a regular basis, so the server can know
     * the client is still alive. Change this value to determine
     * the milliseconds the client should talk to the server if
     * no new commands are being sent
     */
    private int timeOut = 200;

    /**
     * Hold the last time value of the command sent. This will help
     * us determine the last time the value was sent, we can use this
     * for comparison before we can send another value.
     */
    private long timeValueSent = 0; // Time when last value was set

    /**
     * When things like steerMax and and steerMin
     * Change want temp flag so UI can update efficiently instead of all the time
     */
    private boolean settingsChanged = false;

    /**
     * The mapping objects for turning degrees into steer values
     */
    private RangeMapping steerMapping;
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
        this.prevSteer = (int)this.steer;
        this.prevPower = (int)this.power;
        this.steerMapping = new RangeMapping(-0.523f,0.523f,this.steerMax,this.steerMin);
        this.visualSteerMapping = new RangeMapping(-0.523f,0.523f,100.0f,0.0f);
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
     * @returns float - The current power value
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
     * return the power of the car
     * internally this will be from 0 - 100 so need to compensate for min max and invert
     *
     * @return float - the power value
     */
    private float getActualPower()
    {
        // 50 in case of power is stop
        float powerValue;

        /*if(this.power > this.powerMax){
            powerValue = this.powerMax;
        }else if (this.power < this.powerMin){
            powerValue = this.powerMin;
        }else{
            powerValue = this.power;
        }*/

        // Going from 50 - 100 is forward apply forward this.powerMax
        if(this.power >= 50.0f)
            powerValue = RangeMapping.mapValue(this.power, 50.0f, 100.0f, 50.0f, this.powerMax);
        else{
            // Going from 0 - 50 is reverse apply this.powerMin
            powerValue = RangeMapping.mapValue(this.power, 0.0f, 50.0f, this.powerMin, 50.0f);
        }

        if(this.powerInverted)
            powerValue =  this.powerMax - powerValue + (100 - this.powerMax);

        return powerValue;
    }

    /**
     * @see com.confusedbrowser.androneee_remote.models.ModelVehicle:getCommand()
     *
     * @return ArrayList<byte> - A list of bytes which form the command to be sent to the server
     */
    @Override
    public ArrayList<byte[]> getCommands() 
    {
        long currentTime = System.currentTimeMillis();
        boolean somethingToSend = false;

        // Commands are sent as 2 byte packets, the first byte, is the type
        // of command the second is the value.
        ArrayList<byte[]> commands = new ArrayList<byte[]>();

        int steerInt = Math.round(this.actualSteer);
        int powerInt = Math.round(this.getActualPower());
        
        if(steerInt != this.prevSteer || (currentTime-this.timeValueSent > this.timeOut))
        {
            int sendSteer = steerInt+this.steerTrim;
            if (sendSteer > 100) { sendSteer = 100; }
            if (sendSteer < 0) { sendSteer = 0; }
            //Log.d("Dashee", "Steer Value: "+sendSteer);
            // Steering 17 converts to 00010001.
            commands.add(new byte[]{ 17, (byte)(sendSteer << 1) });
            this.prevSteer = steerInt;
            somethingToSend = true;
        }
        
        if(powerInt != this.prevPower || (currentTime-this.timeValueSent > this.timeOut))
        {
            int sendPower = powerInt+this.powerTrim;
            if (sendPower > 100) { sendPower = 100; }
            if (sendPower < 0) { sendPower = 0; }

            // Steering 33 converts to 00100001.
            commands.add( new byte[]{ 33, (byte)(sendPower << 1) });
            this.prevPower = powerInt;
            somethingToSend = true;
        }

        if(somethingToSend)
            this.timeValueSent = System.currentTimeMillis();

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
        this.steer = visualSteerMapping.remapValue(position.getRoll());
        this.actualSteer = this.getActualSteer(position.getRoll());
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
        if(powerControlSlider)
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
        	powerValue = RangeMapping.mapValue(pitch,-1.17f,-0.5f,50.0f, 100.0f); // TODO: invert option
        else if(pitch <=-1.70f) 
        	powerValue = RangeMapping.mapValue(pitch, -2.1f, -1.70f, 0.0f, 50.0f);

        /*if(this.powerInverted)
    		powerValue =  this.powerMax - powerValue + (100 - this.powerMax);*/
    	
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
    private float getActualSteer(float roll)
    {
    	float steerValue = steerMapping.remapValue(roll);
    	if(this.steerInverted)
    		steerValue =  this.steerMax - steerValue + (100 - this.steerMax);
    	return steerValue;
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
        if (value < 0 || value > 100)
            throw new InvalidValue("Value of Max must be from 0-100.");

        settingsChanged = true;

		switch(channel){
			case 1:
                // TODO: Use a custom Exception
                if (value <= this.steerMin)
                    throw new InvalidValue("The Max value must be greater than Min.");

				this.steerMax = value;
				steerMapping.updateTargets(this.steerMax, this.steerMin);
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
        if (value < 0 || value > 100)
            throw new InvalidValue("Value of Max must be from 0-100");

        settingsChanged = true;

		switch(channel){
			case 1:

                // TODO: Use a custom Exception
                if (value > this.steerMax)
                    throw new InvalidValue("The Min value must not be greater than Max.");

				this.steerMin = value;
				steerMapping.updateTargets(this.steerMax, this.steerMin);
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
}
