package com.confusedbrowser.androneee_remote.models;

import java.util.ArrayList;
import java.util.List;

/**
 * This is our interface from which all ModelVehicles
 * are designed
 *
 * @author Shahmir Javaid
 * @author David Buttar
 */
public interface ModelVehicle
{
    /**
     * Build vehicle specific commands to the controller
     * 
     * @return byte array of commands
     */
    List<Byte> getCommands();
    
    /**
     * Converts current phone position to relevant state for the vehicle.
     * 
     * @param position - Current position of the phone.
     */
    public void setFromPhonePosition(ModelPhonePosition position);
    
    /**
     * Set the trim value for channel.
     * 
     * @param channel - Desired channel number.
     * @param value - Desired trim value.
     */
    public void setTrim(int channel, int value);
	
	/**
     * Set the trim value for channel.
     * 
     * @param channel - Desired channel number.
     * @param value - Desired invert bool.
     */
    public void setInvert(int channel, boolean value);

	/**
     * Set the min value for channel.
     * 
     * @param channel - Desired channel number.
     * @param value - Set desired min.
     */
    public void setMin(int channel, float value);

	/**
     * Set the max value for channel.
     * 
     * @param channel - Desired channel number.
     * @param value - Set desired man.
     */
    public void setMax(int channel, float value);

	/**
     * Use on screen sliders to set power value.
     * 
     * @param sliderPos - Current position of the slider.
     */
	public void setFromSlider(int sliderPos);

    /**
     * Use pitch to control power
     *
     * @param value - Set it to use pitch or not
     */
    public void setPowerToUsePitch(boolean value);
}
