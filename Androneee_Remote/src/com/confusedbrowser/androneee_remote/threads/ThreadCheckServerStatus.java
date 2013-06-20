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
     * Context of this object. 
     */
    //private Context context;
    
    /**
     *  Networking variables.
     *   ip - The ip address to connect to
     *   port - The port to connect to
     *   socket - The socket handling wrapper
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
     * Handle to our ModelServerState, to get port and other values.
     */
    private ModelServerState modelServerState;

    /**
     * Initiate our thread. Set the variables from the params, and 
     * set our ipAdress object. Also create a new instance of socket 
     *
     * @param context - The context of this thread
     * @param ip - The ip address to send the commands to
     * @param roll - The default position which is to be set
     */
    public ThreadCheckServerStatus(ModelServerState modelServerState, String ip)
    {
        super();
        try
        {
            this.modelServerState = modelServerState;
            this.setIp(ip);
            this.sockHandler = new DatagramSocket();
            this.sockHandler.setSoTimeout(this.timeOut);
        }
        catch(Exception e)
        {
            e.printStackTrace();
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
            try 
            {
                synchronized (lockIp)
                {
                    // first byte sets the protocol and the channel number
                    // second byte will set the position
                    byte command[] = new byte[]{ 7 };

                    // Create the packet
                    DatagramPacket packet = new DatagramPacket(
                            command, 
                            command.length, 
                            this.ip, 
                            modelServerState.getControlPort()
                        );

                    // Send the packet
                    this.sockHandler.send(packet);

                    byte[] value = new byte[1];
                    packet = new DatagramPacket(value, value.length);
                    this.sockHandler.receive(packet);
                    if (value[0] == (byte)128)
                        modelServerState.setStatusControls(true);
                    else
                        modelServerState.setStatusControls(false);
                    
                    Thread.sleep(this.timeOut);
                }
            }
            catch (SocketTimeoutException e)
            {
                e.printStackTrace();
            }
            catch (Exception e) 
            {
                e.printStackTrace();
            }
            finally
            {
                modelServerState.setStatusControls(false);
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
