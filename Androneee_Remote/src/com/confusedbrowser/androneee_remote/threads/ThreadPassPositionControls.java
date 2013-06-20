package com.confusedbrowser.androneee_remote.threads;

import android.util.Log;
import java.net.*;

import com.confusedbrowser.androneee_remote.models.ModelServerState;

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
     *  Position of the servo.
     *  position - Holds the current position
     *  lastPosition - Holds the last transmitted position 
     */
    private int roll = 50;
    private int prevRoll;
    
    /**
     * The magnitude of power required
     */
    private int power = 0;
    private int prevPower;
    
    /**
     *  Networking variables.
     *  ip - The ip address to connect to
     *  socket - The socket handling wrapper
     */
    private InetAddress ip;
    private DatagramSocket sockHandler;
    
    /**
     * Locking objects.
     * lockPause is used to make the run thread wait and
     * a wrapper to change the pause variable
     * lockPosition is used to lock when getting/setting position
     */
    private Object lockPause = new Object();
    private Object lockPosition = new Object();
    private Object lockIp = new Object();

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
     * Initiate our thread. Set the variables from the params, and 
     * set our ipAdress object. Also create a new instance of socket 
     * @param ip - The ip address to send the commands to
     * @param roll - The default position which is to be set
     */
    public ThreadPassPositionControls(ModelServerState modelServerState, String ip)
    {
        super();
        try
        {
        	this.modelServerState = modelServerState;
            this.prevRoll = this.roll;
            //this.timeLastBpsReset = System.currentTimeMillis();
            this.setIp(ip);
            this.sockHandler = new DatagramSocket();
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }
        
    /**
     * Set the position variable.
     * Lock using lockPosition before setting the this.position
     * value with the parameter
     *
     * @param roll - The position to set
     * @param power - The pitch
     */
    public void update(int roll, int power)
    {
        synchronized (lockPosition)
        {
            this.roll = roll;
            this.power = power;
        }
    }
    
    /**
     * Set the ip and ipObject.
     * try setting ipObject using an ipAddress. If all is well
     * then also change the ip variable
     *
     * @param ip - The ipaddress in a string
     */
    public void setIp(String ip)
    {
        synchronized (lockIp)
        {
            try
            {
            	Log.d("Androneee", "Androneee ip is:"+ip);
                this.ip = InetAddress.getByName(ip);
            }
            catch(Exception e)
            {
                //throw e;
                e.printStackTrace();
            }
        }
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
            synchronized (lockPosition)
            {
                //long currentTime = System.currentTimeMillis();
                // Good for debugging Log.i("position", "Position: " + this.position);    
                synchronized (lockIp)
                {
                	// If the previous position is different send the values to our server.
                	if(this.roll != this.prevRoll)
                		this.sendRollCommand();
                	if(this.power != this.prevPower) 
                		this.sendPowerCommand();
                }
            }
            
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
     * Converts current roll value to androneee server protocol and sends it.
     */
    private void sendRollCommand(){
    	// Commands are sent as 2 byte packets, the first byte, is the type
		// of command the second is the value, 17 converts to 00010001.
		byte command[] = new byte[]{ 17, (byte)(this.roll << 1) };
		this.sendCommandBytes(command);
        this.prevRoll = this.roll;
        this.bytesPerSec++;
    }
    

    /**
     * Converts current power value to androneee server protocol and sends it.
     */
    private void sendPowerCommand(){
    	// Commands are sent as 2 byte packets, the first byte, is the type
		// of command the second is the value, 33 converts to 00100001.
		byte command[] = new byte[]{ 33, (byte)(this.power << 1) };
		this.sendCommandBytes(command);
        this.prevPower = this.power;
        this.bytesPerSec++;
    }
    
    /**
     * Passes androneee server protocol commands to the server.
     */
    private void sendCommandBytes(byte[] command){
    	try
    	{
	        DatagramPacket packet = new DatagramPacket(
	                command, 
	                command.length,
	                this.ip, 
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
