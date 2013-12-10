/**
 * @file include/dashee/Vehicle.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */
#ifndef DASHEE_MODEL_H_
#define DASHEE_MODEL_H_

#include <queue>

#include <dashee/Exception/Vehicle.h>

#include <dashee/ServoController.h>
#include <dashee/Server.h>
#include <dashee/Config.h>

namespace dashee
{
    class Vehicle;
}

/**
 * Virtual Vehicle class.
 *
 * The model class allows to change the model type
 * of the current system, For example the way Plane's
 * are delt is different to Quadcopter or Helicopters.
 *
 * For this you need a middle man, which converts the channel
 * values comming from the client and converts them into a correct model of
 * the plane.
 *
 * For example PITCH UP on on a Multirotor or a Helicopter requires to set
 * the value of two channels. Where as a normal Plane mostly requires a pass 
 * through straight to the controls.
 *
 *
 */
class dashee::Vehicle
{
protected:

    /**
     * The pointer to our servocontroller
     */ 
    dashee::ServoController * servoController;
    
    /**
     * The value that represent our 4 major
     * control surfaces. Each value is within the 
     * range of 0-255
     */
    unsigned short int pitch;
    unsigned short int roll;
    unsigned short int yaw;
    unsigned short int throttle;

    /**
     * This trim value is represented
     * in +/- values, which have to be 
     * within the range of -128 and 128 
     */ 
    signed short int pitchTrim;
    signed short int rollTrim;
    signed short int yawTrim;
    signed short int throttleTrim;

    /**
     * Fallback values represent the value
     * that corresponding control surface will
     * be set to when fallback is called
     */
    unsigned short int pitchFallback;
    unsigned short int rollFallback;
    unsigned short int yawFallback;
    unsigned short int throttleFallback;

    /**
     * Simple variable that controls the fallback
     * flag for each control surface
     */ 
    bool pitchFallbackEnabled;
    bool rollFallbackEnabled;
    bool yawFallbackEnabled;
    bool throttleFallbackEnabled;

    /**
     * Repreents the models current
     * fallback state. This is required by
     * revert and fallback to act on
     */ 
    bool fallbackMode;
    
    // Construct our model
    Vehicle(
            ServoController * servoController, 
            Config * conf = NULL
        );
    
    // Helpfull function for setYaw/setRoll/setPitch and setThrottle
    void setControl(unsigned short int & control, unsigned short int value);
    void setControlTrim(signed short int & control, signed short int value);

public:

    // Loads from the configuration file
    virtual void loadFromConfig(Config * conf);

    // Simple functions which represnt the flight controls
    // of any model
    virtual void setPitch(unsigned short int pitch);
    virtual unsigned short int getPitch(bool notrim = false);

    virtual void setRoll(unsigned short int roll);
    virtual unsigned short int getRoll(bool notrim = false);

    virtual void setYaw(unsigned short int yaw);
    virtual unsigned short int getYaw(bool notrim = false);

    virtual void setThrottle(unsigned short int throttle);
    virtual unsigned short int getThrottle(bool notrim = false);

    // Sets for trim values
    void setPitchTrim(signed short int pitchTriam);
    signed short int getPitchTrim();

    void setRollTrim(signed short int rollTrim);
    signed short int getRollTrim();

    void setYawTrim(signed short int yawTrim);
    signed short int getYawTrim();

    void setThrottleTrim(signed short int throttleTrim);
    signed short int getThrottleTrim();

    // Sets form the fallbacks
    void setPitchFallback(unsigned short int pitch);
    unsigned short int getPitchFallback();

    void setRollFallback(unsigned short int roll);
    unsigned short int getRollFallback();

    void setYawFallback(unsigned short int yaw);
    unsigned short int getYawFallback();

    void setThrottleFallback(unsigned short int throttle);
    unsigned short int getThrottleFallback();

    // Set and get ServoController
    void setServoController(ServoController * servoController);
    ServoController * getServoController();

    // Simple function to return the value of fallbackMode
    bool isFallback();

    // Update our model from a buffer stored in queue
    virtual void read(std::queue<unsigned char> * buffer) = 0;

    // Update our physical model
    virtual void update() = 0;

    // Function which initiate fallback mode
    virtual void fallback();

    // Function which will revert the Vehicle to its original state
    virtual void revert();

    // Destruct virtual so lower level can override
    virtual ~Vehicle();
};

#endif
