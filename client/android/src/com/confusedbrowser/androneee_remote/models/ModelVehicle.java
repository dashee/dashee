package com.confusedbrowser.androneee_remote.models;

import java.util.ArrayList;


public interface ModelVehicle {
	
    /**
     * Build vehicle specific commands to the controller
     * 
     * @return byte array of commands
     */
    ArrayList<byte[]> getCommands();
    
    /**
     * Converts current phone position to relevant state for the vehicle.
     * 
     * @param position - Current position of the phone.
     */
    void setFromPhonePosition(ModelPhonePosition position);
    
    /**
     * Set the trim value for channel.
     * 
     * @param channel - Desired channel number.
     * @param value - Desired trim value.
     */
	void setTrim(int channel, int value);
	
	
	/**
     * Set the trim value for channel.
     * 
     * @param channel - Desired channel number.
     * @param value - Desired invert bool.
     */
	void setInvert(int channel, boolean value);

	/**
     * Set the min value for channel.
     * 
     * @param channel - Desired channel number.
     * @param value - Set desired min.
     */
	void setMin(int channel, float value);

	/**
     * Set the max value for channel.
     * 
     * @param channel - Desired channel number.
     * @param value - Set desired man.
     */
	void setMax(int channel, float value);
}
