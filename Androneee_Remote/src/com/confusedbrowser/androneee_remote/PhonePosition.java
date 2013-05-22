package com.confusedbrowser.androneee_remote;

import java.util.Observable;

import android.content.Context;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.hardware.Sensor;

/*
 * This Class allows monitoring of various user phone movements
 * such as yaw. pitch and roll. 
 */

public class PhonePosition extends Observable implements SensorEventListener {
	private SensorManager mSensorManager;
	private Sensor rotationSensor;
	private float[] m_rotationMatrix = new float[16];
	private float[] m_orientation = new float[4];

	public float roll_val = m_orientation[1];

	public PhonePosition(Context cont)
	{
		mSensorManager = (SensorManager) cont.getSystemService(Context.SENSOR_SERVICE);
		rotationSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_ROTATION_VECTOR);
	}

	@Override
	public void onAccuracyChanged(Sensor sensor, int accuracy) {
		// TODO Auto-generated method stub
		
	}
	
	public void monitor(){
		mSensorManager.registerListener(this, rotationSensor, SensorManager.SENSOR_DELAY_NORMAL);
	}
	
	public void stopMonitor(){
		mSensorManager.unregisterListener(this);
	}

	@Override
	public void onSensorChanged(SensorEvent event) {
		SensorManager.getRotationMatrixFromVector (m_rotationMatrix, event.values);
		SensorManager.getOrientation(m_rotationMatrix, m_orientation);
        /*float yaw_val = m_orientation[0] * 57.2957795f;
        float pitch_val = m_orientation[2] * 57.2957795f;*/
        roll_val = m_orientation[1];

        setChanged();
        notifyObservers();
	}
}
