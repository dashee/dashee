/**
 * This is a class which handels communications with the Pololu board
 * it is a wrapper over the read and write commands sent to usually /dev/ttyACM0
 * 
 * The /dev/ttyACM0 is OS dependant, and be use a later Numerical value if the OS
 * alread has a device running with the similar name
 * 
 * You can see the full documentaion of the Pololu boart at http://www.pololu.com/docs/0J40/all
 * Please read and understand the above to understand in detail the protocol's used in this code
 *
 * @author Shahmir Javaid
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
        
        /**
         * This variable is set during the construct
         * It represents the textual format of the file currently open
         * Great for debugging purposes. And as this class is called once
         * this should only be set once, so it wont add a performance hit on runtime
         * unless the object is being created every time
         */
        const char * dev;

        /**
         * Given our @dev variable we open this device, which returns the appropriate
         * file handler.
         */
        int fd;
    
    protected:
        
    public:
        //Open our Servo Device
        Servo(const char *);

        //Get the last error from the board
        short int getError();

        //Get the target of a given channel
        short int getTarget(const unsigned char);

        //Set the target of a given channel
        void setTarget(const unsigned char, const short int);

        //Calculate the Target, turn 0-100 to be from 3968-8000
        void calculateTarget(short int &);
    
        //TODO: get all the channel values from the board
        int getChannels();
        
        //Close the device
        ~Servo();
};

#endif
