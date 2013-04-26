/**
 * This class defines the implementation required for the Servo classes
 * you should be able to control a servo using some major public functions
 * defined here
 */

#ifndef SERVO_H
#define SERVO_H

#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "Exception/Servo.h"

class Servo
{
    private:
        
    protected:
        
    public:
        //Get the last error from the board
        virtual short int getError() = 0;

        //Get the target of a given channel
        virtual short int getTarget(const unsigned char) = 0;

        //Set the target of a given channel
        virtual void setTarget(const unsigned char, const short int) = 0;

        //Calculate the Target, turn 0-100 to be from 3968-8000
        virtual void calculateTarget(short int &);
    
        //TODO: get all the channel values from the board
        virtual int getChannels() = 0;
};

#endif
