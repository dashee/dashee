package com.confusedbrowser.androneee_remote;

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
public class PhonePosition extends Observable implements SensorEventListener 
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
    public PhonePosition(Context cont)
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
        return this.orientation[1];
    }
    
    /**
     * Return the roll value from the sensor.
     * The 3rd element of the orientation array, holds the roll
     * value
     * 
     * @return float - The orientation value
     */
    public float getPitch()
    {
    	return this.orientation[2];
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
