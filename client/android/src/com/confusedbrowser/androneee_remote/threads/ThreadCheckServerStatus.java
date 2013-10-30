package com.confusedbrowser.androneee_remote.threads;


import android.util.Log;

import java.net.*;

import com.confusedbrowser.androneee_remote.models.*;

/**
 * Thread to check alive status of servers.
 *
 * @author David Buttar
 * @author Shahmir Javaid
 */
public class ThreadCheckServerStatus extends Thread 
{
    /**
     * DatagramSocket to send commands over UDP
     */
    private DatagramSocket sockHandler;
    
    /**
     * The lock object, used when during pause
     */
    private final Object lockPause = new Object();

    /**
     *  Variable controlling the pause state of this thread.
     *  When the onPause function is called this is changed to true
     *  which in turn will call wait on lockPause.
     */
    private boolean pause = false;

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
     * Handle to our ModelServerState, to get port and other values.
     */
    private ModelServerState modelServerState;

    /**
     * Initiate our thread. Set the variables from the parameter, and 
     * set our ipAdress object. Also create a new instance of socket 
     *
     * @param modelServerState - the data model to change
     */
    public ThreadCheckServerStatus(ModelServerState modelServerState)
    {
        super();
        try
        {
            this.modelServerState = modelServerState;
            this.sockHandler = new DatagramSocket();
            this.sockHandler.setSoTimeout(this.timeOut);
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }

    /**
     * Set the position. If a position presented is different than
     * the previous position, notify our server over UDP. If we stop sending 
     * signals to our servers the server will revert to fallback mode, to prevent
     * this we periodically send the same signal back to the server to tell it we
     * are still alive.
     *
     * Also if the Thread is paused, our lockPause object will wait. We know the 
     * thread is paused if the pause variable is true
     */
    public void run() 
    {   
        while(true)
        {
            try 
            {
                Thread.sleep(this.timeOut);

                // first byte sets the protocol and the channel number
                // second byte will set the position
                byte command[] = new byte[]{ 7 };

                // Create the packet
                DatagramPacket packet = new DatagramPacket(
                    command,
                    command.length,
                    this.modelServerState.getIp(),
                    this.modelServerState.getControlPort()
                );

                // Send the packet
                //this.sockHandler.send(packet);

                byte[] value = new byte[1];

                packet = new DatagramPacket(value, value.length);
                this.sockHandler.receive(packet);
                if (value[0] == (byte)128)
                    this.modelServerState.setStatusControls(true);
                else
                    this.modelServerState.setStatusControls(false);
            }
            catch (SocketTimeoutException ignored)
            {
                //Log.d("Dashee", "socket timedout");
            }
            catch (Exception e) 
            {
                e.printStackTrace();
            }
            finally
            {
                this.modelServerState.setStatusControls(false);
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
                    catch (InterruptedException ignored) {}
                }
            }
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
