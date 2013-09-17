/**
 * @file src/Servo.h
 * @author Shahmir Javaid
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. In general
 * you are free to copy, distribute, display, and perform the work, 
 * you are also free to make derivative works, under the following conditions:
 *  - Attribution    — You must give dashee's author credit.
 *  - Non-Commercial - You may not use this dashee for commercial 
 *                     purposes without permission.
 *  - Share Alike    — If you alter, transform, or build upon this work, 
 *                     you may distribute the resulting work only under a licence 
 *                     identical to this one.
 *
 * The terms and conditions are updated at http://dashee.co.uk/license. View the
 * project site for more details
 */

#ifndef SERVO_H_
#define SERVO_H_

#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <dashee/Log.h>

#include "Exception/Servo.h"

/**
 * Servo abstraction.
 *
 * This class defines the implementation required for the Servo classes
 * you should be able to control a servo using some major public functions
 * defined here
 */
class Servo
{
private:
    
protected:
    
    /** 
     * This struct holds the values structures of the settings that
     * a servo can hold, we also, have to set all values to 0, see
     * Constructor, 
     *
     * @instance fallbacks - The values of target, speed and acceleration
     *                       which are set in fallback mode
     * @instance defaults - The default value of the servo, given the target
     *                      speed and acelleration
     * @instance current - The current values of the servo, given the target
     *                     speed and acelleration, set when fallback is called
     *                     and used for revert to set values back to normal
     * @instance fallbackEnabled - The fallbackEnabled instance of this struct
     *                             represents boolean to represent wheather a specific modules
     *                             fallback mode is enabled or not. 0 here represents disabled, > 0
     *                             represents enabled. The 
     */
    struct
    {
        unsigned short int target;
        unsigned short int speed;
        unsigned short int acceleration;
    } fallbacks, defaults, current, fallbackEnabled;

    /** 
     * The channel this Servo class represents
     */
    unsigned short int channel;

    // Set the @dev
    explicit Servo(const unsigned short int channel);
    
public:

    // Get the target of a given channel
    virtual unsigned short int getTarget() = 0;

    // Set the target of a given channel
    virtual void setTarget(unsigned short int) = 0;
    
    // Set the struct defaults.target and call setTarget
    virtual void setTargetDefault(unsigned short int);
    
    // Set the struct fallbacks.target
    virtual void setTargetFallback(unsigned short int);
    
    // Set the struct fallbacks.target
    virtual void setTargetFallbackEnabled(bool);
    
    // Call fallback on this servo
    virtual void fallback();
    
    // revert back to last known values
    virtual void revert();

    // Calculate the Target, turn 0-100 to be from 3968-8000
    void PercentageToTarget(unsigned short int *);

    // Calculate the Target, turn 0-100 to be from 3968-8000, and return the value
    unsigned short int PercentageToTarget(unsigned short int);

    // Calculate the Target, turn 0-100 to be from 3968-8000
    void TargetToPercentage(unsigned short int *);

    // Calculate the Target, turn 0-100 to be from 3968-8000, and return the value
    unsigned short int TargetToPercentage(unsigned short int target);
    
    // Destroy all internals, before cleanup
    virtual ~Servo(){};
};

#endif
