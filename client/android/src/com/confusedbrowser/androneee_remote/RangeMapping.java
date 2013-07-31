package com.confusedbrowser.androneee_remote;

/*
 * Allows to set up generic range mappings
 * e.g. map a value in the range 1..100 (say 10) to 1..1000 which should
 * respond with 100. 
 */

public class RangeMapping
{
	
	//Figure out how 'wide' each range is
    private float leftSpan;
    private float rightSpan;
    
    private float curMin;
    private float curMax;
    private float targetMin;
    private float targetMax;

    /**
     * Set up a new range function
     * 
     * @param curMin - Current range min
     * @param curMax - Current range max
     * @param targetMin - Current range min
     * @param targetMax - Current range max
     * 
     */
    public RangeMapping(float curMin, float curMax, float targetMin, float targetMax)
    {
    	this.curMin = curMin;
    	this.curMax = curMax;
    	this.targetMin = targetMin;
    	this.targetMax = targetMax;
    	
    	//Figure out how 'wide' each range is
        this.leftSpan = curMax - curMin;
        this.rightSpan = targetMax - targetMin;
    }
    
    
    /**
     * Set up a new range function
     * 
     * @param curMin - Current range min
     * @param curMax - Current range max
     * @param targetMin - Current range min
     * @param targetMax - Current range max
     * 
     */
    public void updateTargets(float targetMin, float targetMax)
    {
    	this.targetMin = targetMin;
    	this.targetMax = targetMax;
    	
    	//Figure out how 'wide' each range is
        this.leftSpan = this.curMax - this.curMin;
        this.rightSpan = this.targetMax - this.targetMin;
    }
    
    /**
     * Generic function. Takes a numeric value which is a value in the curMin to curMax range
     * and converts it to a corresponding value in the targetMin to targetMax range.
     * @param value - The numeric value to be re-mapped
     *
     * @return float - Value mapped to the new target range
     */
    public float remapValue(float value)
    {   
        //Convert the left range into a 0-1 range (float)
        float valueScaled = (value - this.curMin) / (this.leftSpan);
        
        //Convert the 0-1 range into a value in the right range.
        if(value < this.curMin)
        	return this.targetMin;
        if(value > this.curMax) 
        	return this.targetMax;
        
        return targetMin + (valueScaled * rightSpan); 
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
    public static float mapValue(float value, float curMin, float curMax, float targetMin, float targetMax)
    {
        //Figure out how 'wide' each range is
        float leftSpan = curMax - curMin;
        float rightSpan = targetMax - targetMin;
        
        //Convert the left range into a 0-1 range (float)
        float valueScaled = (value - curMin) / (leftSpan);
        
        //Convert the 0-1 range into a value in the right range.
        if(value < curMin)
        	return targetMin;
        if(value > curMax) 
        	return targetMax;
        
        return targetMin + (valueScaled * rightSpan); 
    }
}
