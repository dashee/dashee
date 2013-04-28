/**
 * This class defines the implementation required for the Servo classes
 * you should be able to control a servo using some major public functions
 * defined here
 *
 * @author Shahmir Javaid
 */

#ifndef SERVO_H_
#define SERVO_H_

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
        
        /**
         * This variable is set during the construct
         * It represents the textual format of the file currently open
         * Great for debugging purposes. And as this class is called once
         * this should only be set once, so it wont add a performance hit on runtime
         * unless the object is being created every time
         */
        const char * dev;
        
        //Set the @dev
        explicit Servo(const char *);
        
    public:
        
        //Set the @dev
        explicit Servo(){};

        //Get the last error from the board
        virtual short int getError() = 0;

        //Get the target of a given channel
        virtual unsigned short int getTarget(const unsigned char) = 0;

        //Set the target of a given channel
        virtual void setTarget(const unsigned char, unsigned short int) = 0;

        //Calculate the Target, turn 0-100 to be from 3968-8000
        virtual void calculateTarget(unsigned short int &);
    
        //TODO: get all the channel values from the board
        virtual int getChannels() = 0;

        virtual ~Servo(){};
};

#endif
