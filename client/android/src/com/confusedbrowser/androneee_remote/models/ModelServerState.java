package com.confusedbrowser.androneee_remote.models;

import android.util.Log;
import java.net.*;
import java.util.Observable;

/**
 * The Server State Model
 * 
 * This Class allows monitoring of various user phone movements.
 * yaw, pitch and roll are calculated and updated to the observer
 *
 * @author David Buttar
 * @author Shahmir Javaid
 */
public class ModelServerState 
	extends Observable
{
    /**
     * ENUM which represents change types.
     * the @whatChanged variable is set to 
     * one of these values to tell the user what
     * value was changed when the observer is called.
     */
    public enum Notifier
    {
        STATUS_CONTROLS,
        STATUS_TELEMETRY,
        STATUS_FPV,
        PORT_CONTROLS,
        PORT_TELEMETRY,
        PORT_FPV,
        IP,
        NOTHING
    }

    /**
     * Variables that hold the connections state of 
     * there respective servers.
     */
    protected boolean statusControls = false;
    protected boolean statusTelemetry = false;
    protected boolean statusFpv = false;
    
    /**
     * These variables hold the port number for different 
     * Server types. These are used by connecting threads, and
     * other objects, so it makes sense to have it in a shared
     * object.
     */
    private int portControls = 2047;
    private int portTelemetry = 2048;
    private int portFpv = 2049;
    
    /**
     * This is the server's ipAddress.
     */
    protected InetAddress ip;

    /**
     * This variable is responsible for controlling
     * what is considered a full systems failure.
     * true - represents that one or more or all servers failed are considered as 
     *        a loss of connection
     * false - represents that all servers must fail before a connection 
     *         can be deemed as lost.
     */
    protected boolean strict = false;

    /**
     * Initialise our variables
     */
    public ModelServerState()
    {
        this.setIp("192.168.1.12");
    }
    
    /**
     * This will set statusControl value, and inform.
     * the observer if the previous value was not the same
     * Helpful when you want to detect a connection success or failure
     *
     * @param controls - The value to be set
     */
    public void setStatusControls(boolean status)
    {
        // The state has changed so notify
        if (this.statusControls != status)
        {
            this.statusControls = status;
            setChanged();
            notifyObservers(Notifier.STATUS_CONTROLS);
        }
    }
    
    /**
     * This will set statusControl value, and inform.
     * the observer if the previous value was not the same
     * Helpful when you want to detect a connection success or failure
     *
     * @param controls - The value to be set
     */
    public void setStatusTelemetery(boolean status)
    {
        // The state has changed so notify
        if (this.statusTelemetry != status)
        {
            this.statusTelemetry = status;
            setChanged();
            notifyObservers(Notifier.STATUS_TELEMETRY);
        }
    }
    
    /**
     * This will set statusFpv value, and inform.
     * the observer if the previous value was not the same
     * Helpful when you want to detect a connection success or failure
     *
     * @param controls - The value to be set
     */
    public void setStatusFpv(boolean status)
    {
        // The state has changed so notify
        if (this.statusFpv != status)
        {
            this.statusFpv = status;
            setChanged();
            notifyObservers(Notifier.STATUS_FPV);
        }
    }
    
    /**
     * Set the Controls port value.
     *
     * @param int - A port greater than 1000, and not the same as telemetry or FPV
     */
    public void setControlsPort(int port)
    {
        if (port > 1000 && (port != this.portTelemetry || port != this.portFpv))
        {
            this.portControls = port;
            setChanged();
            notifyObservers(Notifier.PORT_CONTROLS);
        }
    }
    
    /**
     * Set the Telemetry port value.
     *
     * @param int - A port greater than 1000, and not the same as Controls or Fpv
     */
    public void setTelemetryPort(int port)
    {
        if (port > 1000 && (port != this.portControls || port != this.portFpv))
        {
            this.portTelemetry = port;
            setChanged();
            notifyObservers(Notifier.PORT_TELEMETRY);
        }
    }
    
    /**
     * Set the FPV port value.
     *
     * @param int - A port greater than 1000, and not the same as Controls or Telemetry
     */
    public void setFpvPort(int port)
    {
        if (port > 1000 && (port != this.portControls || port != this.portTelemetry))
        {
            this.portFpv = port;
            setChanged();
            notifyObservers(Notifier.PORT_FPV);
        }
    }
    
    /**
     * Change the IP address
     *
     * @param ip - The IP address value in string
     */
    public void setIp(String ip)
    {
        try
        {
            this.ip = InetAddress.getByName(ip);
            setChanged();
            notifyObservers(Notifier.IP);
        }
        catch(Exception ex)
        {
            Log.e("Dashee", "setIp failed");
            ex.printStackTrace();
        }
    }
    
    /**
     * Get the IP string
     *
     * @returns InetAddress - The IP address
     */
    public InetAddress getIp()
    {
        return this.ip;
    }
    
    /**
     * Get the control port.
     *
     * @return int - The port number
     */ 
    public int getControlPort()
    {
        return this.portControls;
    }
    
    /**
     * This will return the alive state of the server.
     * In strict mode, true is returned only if all servers are connected
     * otherwise true is returned if any one of the servers are 
     *
     * @param strict - True it is strict, false otherwise
     *
     * @returns boolean - the server state
     */
    public boolean isAlive(boolean strict)
    {
        if (strict)
            return (statusControls && statusTelemetry && statusFpv);
        else
            return (statusControls || statusTelemetry || statusFpv);
    }

    /**
     * non-strict mode of isAlive(boolean) function
     *
     * @returns boolean - the server state
     */
    public boolean isAlive()
    {
        return this.isAlive(false);
    }
}
