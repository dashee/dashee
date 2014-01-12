/**
 * @file include/dashee/Hardware/Servo.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_HARDWARE_SERVO_H_
#define DASHEE_HARDWARE_SERVO_H_

#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <dashee/common.h>
#include <dashee/Log.h>
#include <dashee/Hardware/Exception/Servo.h>

namespace dashee
{
    namespace Hardware
    {
        class Servo;
    }
}

/**
 * Servo abstraction.
 *
 * This class defines the implementation required for the Servo classes
 * you should be able to control a servo using some major public functions
 * defined here
 */
class dashee::Hardware::Servo
{
private:
    
protected:
    
    /** 
     * The channel this Servo class represents
     */
    unsigned short int channel;

    /**
     * This function gets and stores the last value
     * that the target was set to
     */
    unsigned short target;
    
    // Set the @dev
    explicit Servo(
            const unsigned short int channel,
            unsigned short int target = 0
        );
    
public:

    const unsigned short int SERVO_LOW;
    const unsigned short int SERVO_HIGH;

    // Set the target of a given channel, The cache does not query the actual 
    // servo if it is set to true
    virtual void setTarget(unsigned short int target);
    virtual unsigned short int getTarget(const bool fromcache = false) = 0;
    
    // Destroy all internals, before cleanup
    virtual ~Servo(){};
};

#endif
