/**
 * This class defines the implementation required for the Servo classes
 * you should be able to control a servo using some major public functions
 * defined here
 *
 * @author Shahmir Javaid
 */

#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "Exception/Servo.h"

#ifndef SERVO_H_
#define SERVO_H_

class Servo
{
private:
    
protected:
    
    /** 
     * This struct holds the values structures of the settings that
     * a servo can hold, we also, have to set all values to 0, see
     * Constructor
     */
    struct
    {
        int target;
        int speed;
        int acceleration;
    } fallbacks, defaults, current;

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
    
    // Call fallback on this servo
    virtual void fallback();
    
    // revert back to last known values
    virtual void revert();

    // Calculate the Target, turn 0-100 to be from 3968-8000
    void calculateTarget(unsigned short int &);
    
    // Destroy all internals, before cleanup
    virtual ~Servo(){};
};

#endif
