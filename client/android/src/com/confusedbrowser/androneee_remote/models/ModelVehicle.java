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
	
}
