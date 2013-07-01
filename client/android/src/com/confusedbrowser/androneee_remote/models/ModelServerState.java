package com.confusedbrowser.androneee_remote.models;

import android.util.Log;

import java.net.*;
import java.util.Observable;

/**
 * The Server State Model
 *
 * @author David Buttar
 * @author Shahmir Javaid
 */

/**
 * This Class allows monitoring of various user phone movements.
 * yaw, pitch and roll are calculated and updated to the observer
 */
public class ModelServerState extends Observable
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
        STATUS_TELEMETERY,
        STATUS_FPV,
        PORT_CONTROLS,
        PORT_TELEMETERY,
        PORT_FPV,
        IP,
        NOTHING
    }

    /**
     * Variables that hold the connections state of 
     * there respective servers.
     */
    protected boolean statusControls = false;
    protected boolean statusTelemetery = false;
    protected boolean statusFpv = false;
    
    /**
     * These variables hold the port number for different 
     * Server types. These are used by connecting threads, and
     * other objects, so it makes sense to have it in a shared
     * object.
     */
    private int portControls = 2047;
    private int portTelemetery = 2048;
    private int portFpv = 2049;
    
    /**
     * This is the server's ipAddress.
     */
    protected InetAddress ip;

    /**
     * This variable is responsible for controlling
     * what is considered a full systems failiure.
     * true - represents that one or more or all servers failed are considered as 
     *        a loss of connection
     * false - represents that all servers must fail before a connection 
     *         can be deemed as lost.
     */
    protected boolean strict = false;

    /**
     * Initialize our variables
     */
    public ModelServerState()
    {
        this.setIp("192.168.1.12");
    }
    
    /**
     * This will set statusControl value, and inform.
     * the observer if the previous value was not the same
     * helpfull when you want to detect a connection success or failiure
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
     * helpfull when you want to detect a connection success or failiure
     *
     * @param controls - The value to be set
     */
    public void setStatusTelemetery(boolean status)
    {
        // The state has changed so notify
        if (this.statusTelemetery != status)
        {
            this.statusTelemetery = status;
            setChanged();
            notifyObservers(Notifier.STATUS_TELEMETERY);
        }
    }
    
    /**
     * This will set statusFpv value, and inform.
     * the observer if the previous value was not the same
     * helpfull when you want to detect a connection success or failiure
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
     * @param int - A port greater than 1000, and not the same as Telemetery or Fpv
     */
    public void setControlsPort(int port)
    {
        if (port > 1000 && (port != this.portTelemetery || port != this.portFpv))
        {
            this.portControls = port;
            setChanged();
            notifyObservers(Notifier.PORT_CONTROLS);
        }
    }
    
    /**
     * Set the Telemetery port value.
     *
     * @param int - A port greater than 1000, and not the same as Controls or Fpv
     */
    public void setTelemeteryPort(int port)
    {
        if (port > 1000 && (port != this.portControls || port != this.portFpv))
        {
            this.portTelemetery = port;
            setChanged();
            notifyObservers(Notifier.PORT_TELEMETERY);
        }
    }
    
    /**
     * Set the Fpv port value.
     *
     * @param int - A port greater than 1000, and not the same as Controls or Telemetery
     */
    public void setFpvPort(int port)
    {
        if (port > 1000 && (port != this.portControls || port != this.portTelemetery))
        {
            this.portFpv = port;
            setChanged();
            notifyObservers(Notifier.PORT_FPV);
        }
    }
    
    /**
     * Change the IP address
     *
     * @param ip - The ip address value in string
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
     * Get the Ip string
     *
     * @returns InetAddress - The Ip address
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
            return (statusControls && statusTelemetery && statusFpv);
        else
            return (statusControls || statusTelemetery || statusFpv);
    }

    /**
     * Unstrict mode of isAlive(boolean) function
     *
     * @returns boolean - the server state
     */
    public boolean isAlive()
    {
        return this.isAlive(false);
    }
}
