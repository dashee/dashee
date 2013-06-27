/**
 * 
 */
package com.confusedbrowser.androneee_remote.models;

import java.util.ArrayList;

/**
 * @author shahmirj is a cock
 *
 */
public class ModelVehicleCar implements ModelVehicle {
    
	
    private int steer = 50;
    private int prevSteer;
    
    private int power = 0;
    private int prevPower;
	
    /*
     * Getter for steer
     * 
     * @returns steer
     */
    public int getSteer(){
    	return steer;
    }
    
    /*
     * Getter for power
     * 
     * @returns power
     */
    public int getPower(){
    	return power;
    }
	
	/**
	 * Set up the car vehicle type
	 */
	public ModelVehicleCar() 
	{
		this.prevSteer = this.steer;
		this.prevPower = this.power;
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
		
		if(this.steer != this.prevSteer)
		{
			// Steering 17 converts to 00010001.
			commands.add(new byte[]{ 17, (byte)(this.steer << 1) });
			this.prevSteer = this.steer;
		}
		
		if(this.power != this.prevPower)
		{
			// Steering 33 converts to 00100001.
			commands.add( new byte[]{ 33, (byte)(this.power << 1) });
			this.prevPower = this.power;
		}
		
		return commands;
	}

	/* (non-Javadoc)
	 * @see com.confusedbrowser.androneee_remote.models.ModelVehicle#setFromPhonePosition(com.confusedbrowser.androneee_remote.models.ModelPhonePosition)
	 */
	@Override
	public void setFromPhonePosition(ModelPhonePosition position) 
	{
		
		this.steer = (int) this.getSteer(position.getRoll());
		this.power = (int) this.getPower(position.getPitch());
		
	}

	private float getPower(float pitch) {
		if(pitch >= -0.1f)
    	{
    		return 50.0f;
    	}
    	else if(pitch >= -1.17f)
    	{
    		return remapValue(pitch,-1.17f,-0.5f,50.0f,43.0f); // TODO: invert option
    	}
    	else if(pitch <=-1.70f) 
    	{
    		//return 20.0f;
    		return remapValue(pitch, -2.1f, -1.70f, 60.0f, 50.0f);
    	}
    	return 50.0f;
	}

	private float getSteer(float roll) {
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
