package com.confusedbrowser.androneee_remote.threads;

import java.net.*;
import java.util.ArrayList;

import android.util.Log;

import com.confusedbrowser.androneee_remote.models.ModelServerState;
import com.confusedbrowser.androneee_remote.models.ModelVehicle;

/**
 * Thread to communicate to the server.
 * This will send position when the position is changed and 
 * communicate with the server when the position is the same, so
 * the server can know that we are still alive
 *
 * @author David Buttar
 * @author Shahmir Javaid
 */
public class ThreadPassPositionControls extends Thread 
{
    /**
     * DataGram object to send commnds over UDP
     */
    private DatagramSocket sockHandler;
    
    /**
     * Locking objects.
     * lockPause is used to make the run thread wait and
     * a wrapper to change the pause variable
     * lockPosition is used to lock when getting/setting position
     */
    private Object lockPause = new Object();

    /**
     *  Variable controlling the pause state of this thread.
     *  When the onPause function is called this is changed to true
     *  which in turn will call wait on lockPause.
     */
    private boolean pause = false;
    
    /**
     * Variable controlling the execution of a thread.
     * The run() function runs constantly, so exit variable
     * controls the infinite loop
     */
    private boolean exit = false;

    /**
     * Holds the last time the Bps command was reset. This will help change
     * our view to determine how many bytes have been sent over a second
     * Every time the view is set, the values of this is reset to current time
     */
    //private long timeLastBpsReset = 0;

    /**
     * Hold the value of bytes sent. It will be reset to 0 after every
     * second.
     */
    private int bytesPerSec = 0;
    
    /**
     * Handle to our ModelServerState, to get port and other values.
     */
    private ModelServerState modelServerState;
    
    /**
     * Current vehicle in use.
     */
    private ModelVehicle modelVehicle;
	

    /**
     * Initiate our thread. Set the variables from the params, and 
     * set our ipAdress object. Also create a new instance of socket 
     * @param ip - The ip address to send the commands to
     * @param modelVehicle 
     * @param roll - The default position which is to be set
     */
    public ThreadPassPositionControls(ModelServerState modelServerState, ModelVehicle modelVehicle)
    {
        super();
        try
        {
            this.modelVehicle = modelVehicle;
            this.modelServerState = modelServerState;
            //this.timeLastBpsReset = System.currentTimeMillis();
            this.sockHandler = new DatagramSocket();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }

        Thread.currentThread().setPriority(Thread.MAX_PRIORITY);
    }

    public void setBps(int bps)
    {
        if (bps < 0) bps = 0;

        this.bytesPerSec = bps;
    }

    public int getBps()
    {
        return this.bytesPerSec;
    }
    
    /**
     * Set the position. If a position presented is different than
     * the previous position, notify our server over UDP. If we stop sending 
     * signals to our servers the server will revert to fallback mode, to prevent
     * this we periodically send the same signal back to the server to tell it we
     * are still alive.
     *
     * Also if the Thread is paused, our lockPause object will wait. We know the 
     * thread is paused if the @pause variable is true
     */
    public void run() 
    {   
        while(!exit)
        {

            this.sendCommands();
            
            // We are in lock state, so sent the thread to wait
            // which can be then woken up by a notify
            synchronized (lockPause) 
            {
                while (pause) 
                {
                    try 
                    {
                        lockPause.wait();
                    } 
                    catch (InterruptedException e) 
                    {
                    }
                }
            }
        }
    }
    
    /**
     * Send any available control updates.
     */
    private void sendCommands()
    {
    	ArrayList<byte[]> commands =  this.modelVehicle.getCommands();
    	for(byte[] command : commands)
    	{
            this.sendCommandBytes(command);
    	}
    }
    
    /**
     * Passes dashee server protocol commands to the server.
     */
    private void sendCommandBytes(byte[] command)
    {
        try
        {
        	Log.d("Dashee", "Server using ip: "+this.modelServerState.getIp());
            DatagramPacket packet = new DatagramPacket(
                command, 
                command.length,
                this.modelServerState.getIp(), 
                this.modelServerState.getControlPort()
            );
            this.sockHandler.send(packet);
        } 
        catch (Exception e) 
        {
            e.printStackTrace();
        }
    }
    
    /**
     * Change the pause flag. When we pause
     * the flag will prevent call lockPause.wait();
     * see run for this behaviour
     */
    public void onPause() 
    {
        synchronized (lockPause) 
        {
            pause = true;
        }
    }

    /**
     * Thread is resumed. Change the pause flag
     * and notify all waiting Objects
     */
    public void onResume() 
    {
        synchronized (lockPause) 
        {
            pause = false;
            lockPause.notifyAll();
        }
    }
}
