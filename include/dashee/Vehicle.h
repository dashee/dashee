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

#include <dashee/Hardware/ServoController.h>
#include <dashee/Server.h>
#include <dashee/Config.h>
#include <dashee/Buffer.h>

namespace dashee
{
    class Vehicle;
}

/**
 * Virtual Vehicle class.
 *
 * The model class allows to change the model type
 * of the current system, For example the way Plane's
 * are dealt is different to Quadcopter or Helicopters.
 *
 * For this you need a middle man, which converts the channel
 * values coming from the client and converts them into a correct model of
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
    dashee::Hardware::ServoController * servoController;
    
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
     * These values represent the channel
     * number each of our main control surfaces represent
     */
    unsigned short int pitchChannel;
    unsigned short int rollChannel;
    unsigned short int yawChannel;
    unsigned short int throttleChannel;

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
     * Represents the models current
     * fallback state. This is required by
     * revert and fallback to act on
     */ 
    bool fallbackMode;
    
    // Helpful function for setYaw/setRoll/setPitch and setThrottle
    void setControl(unsigned short int & control, unsigned short int value);
    void setControlTrim(signed short int & control, signed short int value);

public:

    // Construct our model
    Vehicle(
            dashee::Hardware::ServoController * servoController,
            Config * conf = NULL
    );

    // Loads from the configuration file
    virtual void loadFromConfig(Config * conf);

    // Simple functions which represnt the flight controls
    // of any model
    virtual void setPitch(unsigned short int pitch);
    virtual unsigned short int getPitch(bool notrim = false) const;

    virtual void setRoll(unsigned short int roll);
    virtual unsigned short int getRoll(bool notrim = false) const;

    virtual void setYaw(unsigned short int yaw);
    virtual unsigned short int getYaw(bool notrim = false) const;

    virtual void setThrottle(unsigned short int throttle);
    virtual unsigned short int getThrottle(bool notrim = false) const;

    // Overwrite our basic channels
    void setPitchChannel(const unsigned short int value);
    unsigned short int getPitchChannel() const;

    void setRollChannel(const unsigned short int value);
    unsigned short int getRollChannel() const;

    void setYawChannel(const unsigned short int value);
    unsigned short int getYawChannel() const;

    void setThrottleChannel(const unsigned short int value);
    unsigned short int getThrottleChannel() const;

    // Sets for trim values
    void setPitchTrim(signed short int pitchTriam);
    signed short int getPitchTrim() const;

    void setRollTrim(signed short int rollTrim);
    signed short int getRollTrim() const;

    void setYawTrim(signed short int yawTrim);
    signed short int getYawTrim() const;

    void setThrottleTrim(signed short int throttleTrim);
    signed short int getThrottleTrim() const;

    // Sets from the fallback
    void setPitchFallback(unsigned short int pitch);
    unsigned short int getPitchFallback() const;

    void setRollFallback(unsigned short int roll);
    unsigned short int getRollFallback() const;

    void setYawFallback(unsigned short int yaw);
    unsigned short int getYawFallback() const;

    void setThrottleFallback(unsigned short int throttle);
    unsigned short int getThrottleFallback() const;

    // Set and get ServoController
    void setServoController(
            dashee::Hardware::ServoController * servoController
        );
    dashee::Hardware::ServoController * getServoController() const;

    // Simple function to return the value of fallbackMode
    bool isFallback() const;

    // Update our model from a buffer stored in queue
    virtual void read(Buffer<unsigned char> * buffer);

    // Update our physical model
    virtual void update();

    // Function which initiate fallback mode
    virtual void fallback();

    // Function which will revert the Vehicle to its original state
    virtual void revert();

    // Destruct virtual so lower level can override
    virtual ~Vehicle();
};

#endif
