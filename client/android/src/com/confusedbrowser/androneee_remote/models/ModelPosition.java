package com.confusedbrowser.androneee_remote.models;

import android.content.Context;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.hardware.Sensor;

import java.util.Observable;

/**
 * This Class allows monitoring of various user phone movements.
 * yaw, pitch and roll are calculated and updated to the observer
 *
 * @author David Buttar
 * @author Shahmir Javaid
 */
public class ModelPosition extends Observable implements SensorEventListener 
{
    /**
     * required Sensors.
     */
    private SensorManager sensorManager;
    private Sensor rotationSensor;

    /**
     * Holds the rotation Matrix array of floats.
     * Used by the onSensorChanged to update our orientation
     */
    private float[] rotationMatrix = new float[16];

    /**
     * An array of orientation of the phone. Updated by the
     * onSensorChanged event, holds yaw, pitch and roll
     */
    private float[] orientation = new float[4];
    
    /**
     * Initialize our variables
     *
     * @param cont - The context in which to set the sensor in
     */
    public ModelPosition(Context cont)
    {
        this.sensorManager = (SensorManager)cont.getSystemService(Context.SENSOR_SERVICE);
        this.rotationSensor = sensorManager.getDefaultSensor(Sensor.TYPE_ROTATION_VECTOR);
    }
    
    /**
     * Return the roll value from the sensor.
     * The 2nd element of the orientation array, holds the roll
     * value
     * 
     * @return float - The orientation value
     */
    public float getRoll()
    {
        return (100.0f - remapValue(this.orientation[1],-0.523f,0.523f,0.0f,100.0f));
    }
    
    /**
     * Return the roll value from the sensor.
     * The 3rd element of the orientation array, holds the roll
     * value
     * 
     * 
     * @return float - The orientation value
     */
    public float getPitch()
    {   
    	if(this.orientation[2] >= -0.1f)
    	{
    		return 50.0f;
    	}
    	else if(this.orientation[2] >= -1.17f)
    	{
    		return remapValue(this.orientation[2],-1.17f,-0.5f,50.0f,43.0f); // TODO: invert option
    	}
    	else if(this.orientation[2] <=-1.70f) 
    	{
    		//return 20.0f;
    		return remapValue(this.orientation[2], -2.1f, -1.70f, 60.0f, 50.0f);
    	}
    	return 50.0f;
    }
    
    /**
     * Return current Pitch value
     * 
     * @return float - The pitch value in Radians
     */
    public float getPitchRadians()
    {
        return this.orientation[2];
    }
    
    /**
     * Return current Roll value
     * 
     * @return float - The roll value in Radians
     */
    public float getRollRadians()
    {
        return this.orientation[1];
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
    
    
    
    /**
     * When the accuracy is changed, Perform some actions
     *
     * @param sensor - The sensor in question
     * @param accuracy - The accuracy value
     */
    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) 
    {
    }

    /**
     * Resume the sensor.
     */
    public void onResume()
    {
        sensorManager.registerListener(
            this,
            rotationSensor,
            SensorManager.SENSOR_DELAY_FASTEST //Important, use the highest value possible
        );
    }
    
    /**
     * Pause our sensor.
     */
    public void onPause()
    {
        sensorManager.unregisterListener(this);
    }
    
    /**
     * When ever our sensor is changed notify the Observer.
     *
     * This function will notifyObservers of the change of value
     * This object can then access the get function to determine new values
     *
     * @param event - The sensor event
     */
    @Override
    public void onSensorChanged(SensorEvent event) 
    {
        SensorManager.getRotationMatrixFromVector (this.rotationMatrix, event.values);
        SensorManager.getOrientation(this.rotationMatrix, this.orientation);
        setChanged();
        notifyObservers();
    }
}
