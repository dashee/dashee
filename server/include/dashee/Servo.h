/**
 * @file include/dashee/Servo.h
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
 *                     you may distribute the resulting work only under a 
 *                     licence identical to this one.
 *
 * The terms and conditions are updated at http://dashee.co.uk/license. View the
 * project site for more details
 */

#ifndef DASHEE_SERVO_H_
#define DASHEE_SERVO_H_

#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <dashee/common.h>
#include <dashee/Log.h>
#include <dashee/Exception/Servo.h>

namespace dashee
{
    class Servo;
}

/**
 * Servo abstraction.
 *
 * This class defines the implementation required for the Servo classes
 * you should be able to control a servo using some major public functions
 * defined here
 */
class dashee::Servo
{
private:
    
protected:
    
    /** 
     * The channel this Servo class represents
     */
    unsigned short int channel;
    
    // Set the @dev
    explicit Servo(const unsigned short int channel);
    
public:

    const unsigned short int SERVO_LOW;
    const unsigned short int SERVO_HIGH;

    // Set the target of a given channel
    virtual void setTarget(unsigned short int target) = 0;
    virtual unsigned short int getTarget() = 0;
    
    // Destroy all internals, before cleanup
    virtual ~Servo(){};
};

#endif
