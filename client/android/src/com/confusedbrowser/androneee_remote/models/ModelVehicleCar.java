/**
 * 
 */
package com.confusedbrowser.androneee_remote.models;

import java.util.ArrayList;

/**
 * @author shahmirj is a cock
 *
 */
public class ModelVehicleCar implements ModelVehicle 
{
    private float steer = 50;
    private int prevSteer;
    
    private float power = 0;
    private int prevPower;
    
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
     * Set up the car vehicle type
     */
    public ModelVehicleCar() 
    {
        this.prevSteer = (int)this.steer;
        this.prevPower = (int)this.power;
    }

    /* (non-Javadoc)
     * @see com.confusedbrowser.androneee_remote.models.ModelVehicle#getCommand()
     */
    @Override
    public ArrayList<byte[]> getCommands() 
    {
        // Commands are sent as 2 byte packets, the first byte, is the type
        // of command the second is the value.
        ArrayList<byte[]> commands = new ArrayList<byte[]>();
        
        if((int)this.steer != this.prevSteer)
        {
            // Steering 17 converts to 00010001.
            commands.add(new byte[]{ 17, (byte)((int)this.steer << 1) });
            this.prevSteer = (int)this.steer;
        }
        
        if((int)this.power != this.prevPower)
        {
            // Steering 33 converts to 00100001.
            commands.add( new byte[]{ 33, (byte)((int)this.power << 1) });
            this.prevPower = (int)this.power;
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
        this.power = this.getPower(position.getPitch());
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
    private float getPower(float pitch) 
    {
        if(pitch >= -0.1f)
            return 50.0f;
        else if(pitch >= -1.17f)
            return remapValue(pitch,-1.17f,-0.5f,50.0f,43.0f); // TODO: invert option
        else if(pitch <=-1.70f) 
            return remapValue(pitch, -2.1f, -1.70f, 60.0f, 50.0f);

        return 50.0f;
    }

    /**
     * Return the steer value, given the roll of the phone.
     * Steer being 50 is center, 0 is full left and 100 is full right
     *
     * @param roll - the roll value in radians
     *
     * @return float - the steer value
     */
    private float getSteer(float roll) 
    {
        return (100.0f - remapValue(roll,-0.523f,0.523f,0.0f,100.0f));
    }
	
    /**
     * Generic function. Takes a numeric value which is a value in the curMin to curMax range
     * and converts it to a corresponding value in the targetMin to targetMax range.
     * @param value - The numeric value to be re-mapped
     * @param curMin - Current range min
     * @param curMax - Current range max
     * @param targetMin - Current range min
     * @param targetMax - Current range max
     *
     * @return float - Value mapped to the new target range
     */
    private float remapValue(float value, float curMin, float curMax, float targetMin, float targetMax)
    {
        //Figure out how 'wide' each range is
        float leftSpan = curMax - curMin;
        float rightSpan = targetMax - targetMin;
        
        //Convert the left range into a 0-1 range (float)
        float valueScaled = (value - curMin) / (leftSpan);
        
        //Convert the 0-1 range into a value in the right range.
        if(value<curMin) return targetMin;
        if(value>curMax) return targetMax;
        return targetMin + (valueScaled * rightSpan); 
    }
}
