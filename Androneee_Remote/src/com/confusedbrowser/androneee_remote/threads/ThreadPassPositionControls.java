package com.confusedbrowser.androneee_remote.threads;

import android.content.Context;
import android.util.Log;
import java.net.*;

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
     * Context of this object. 
     */
    private Context context;

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
     *  port - The port to connect to
     *  socket - The socket handling wrapper
     */
    private InetAddress ip;
    private int port;
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
     * controls the infinate loop
     */
    private boolean exit = false;

    /**
     * Define the gap when the values are resent. We want
     * to ensure that the client communicates with the
     * server in a regular basis, so the server can know
     * the client is still alive. Change this value to determine
     * the milliseconds the client should talk to the server if
     * no new commands are being sent
     */
    private int timeOut = 500;
    
    /**
     * Hold the last time value of the command sent. This will help
     * us determine the last time the value was sent, we can use this
     * for comparison before we can send another value.
     */
    private long timeValueSent = 0;

    /**
     * Holds the last time the Bps command was reset. This will help change
     * our view to determine how many bytes have been sent over a second
     * Every time the view is set, the values of this is reset to current time
     */
    private long timeLastBpsReset = 0;

    /**
     * Hold the value of bytes sent. It will be reset to 0 after every
     * second.
     */
    private int bytesPerSec = 0;
	

    /**
     * Initiate our thread. Set the variables from the params, and 
     * set our ipAdress object. Also create a new instance of socket 
     *
     * @param context - The context of this thread
     * @param ip - The ip address to send the commands to
     * @param roll - The default position which is to be set
     */
    public ThreadPassPositionControls(Context context, String ip, int port)
    {
        super();
        try
        {
            this.context = context;
            this.prevRoll = this.roll;
            this.timeLastBpsReset = System.currentTimeMillis();
            this.setIp(ip);
            this.port = port;
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
                long currentTime = System.currentTimeMillis();
                // Good for debugging Log.i("position", "Position: " + this.position);    
                synchronized (lockIp)
                {
                	// If the previous position is different or we have reached a timeout
                    // send the values to our server, only one command needs to be send on timeout
                	// so I choose the first one.
                	if(this.roll != this.prevRoll || (currentTime-this.timeValueSent > this.timeOut))
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
     * Calculates roll command in binary to pass to the server
     */
    private void sendRollCommand(){
    	// Commands are sent as 2 byte packets, the first byte, is the type
		// of command the second is the value, 33 converts to 00100001, see androneee server protocol
		byte command[] = new byte[]{ 33, (byte)(this.roll << 1) };
		this.sendCommandBytes(command);
        this.prevRoll = this.roll;
        this.bytesPerSec++;
        this.timeValueSent = System.currentTimeMillis();
    }
    

    /**
     * Calculates power command in binary to pass to the server
     */
    private void sendPowerCommand(){
    	// Commands are sent as 2 byte packets, the first byte, is the type
		// of command the second is the value, 19 converts to 00010011, see androneee server protocol
		byte command[] = new byte[]{ 19, (byte)(this.power << 1) };
		this.sendCommandBytes(command);
        this.prevPower = this.power;
        this.bytesPerSec++;
        this.timeValueSent = System.currentTimeMillis();
    }
    
    /**
     * Passes byte arrays to the server
     */
    private void sendCommandBytes(byte[] command){
    	try
    	{
	    	// Create the packet
	        DatagramPacket packet = new DatagramPacket(
	                command, 
	                command.length,
	                this.ip, 
	                this.port
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
