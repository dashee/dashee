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
        static int retry;
        const char * dev;
        int fd;
        short int channels[32];
    
    protected:
        
    public:
        Servo(const char *);
        int getError();
        int getTarget(const unsigned char);
        void setTarget(const unsigned char, const short int);

        int getChannels();

        ~Servo();
};

#endif
