#include "Servo.h"

Servo::Servo(const char * dev)
{
    this->dev = dev;
    fd = open(this->dev, O_RDWR | O_NOCTTY);
    
    //Default the values
    std::fill_n(channels, 32, -1);

    if (fd == -1)
        throw Exception_Servo();
}

Servo::~Servo()
{
    close(this->fd);    
}

int Servo::getError()
{
    unsigned char command[] = { 0xA1 };
    unsigned char response[2];

    if (write(fd, command, sizeof(command)) == -1)
        throw Exception_Servo();
    
    if(read(fd,response,2) != 2)
        throw Exception_Servo();

    return (int)sqrt(response[0] + 256*response[1]);
}

int Servo::getTarget(const unsigned char channel)
{
    unsigned char command[2];
    command[0] = 0x90;
    command[1] = channel;

    if(write(this->fd, command, sizeof(command)) == -1)
        throw Exception_Servo();

    unsigned char response[2];
    if(read(fd,response,2) != 2)
        throw Exception_Servo();

    return response[0] + 256*response[1];
}

void Servo::setTarget(const unsigned char channel, short int target)
{
    calculateTarget(target);
 
    unsigned char command[4];
    command[0] = 0x84;
    command[1] = channel;
    command[2] = target & 127;
    command[3] = (target >> 7) & 127;

    if (write(this->fd, command, sizeof(command)) == -1)
        throw Exception_Servo();
    
    //Set the target
    channels[(short int)channel] = target;
}

void Servo::calculateTarget(short int & target)
{
    if (target >= 0 && target <= 100)
    {
        // If it is 1, set to 0% value
        if (target == 0) 
            target = 3968;

        // Other wise set to 100% value
        else if (target == 100)
            target = 8000;

        // Other wise get a percentage number between the range
        // 992-8000, Note that for calculations sake we calculate from 0-7008
        // then add 992, to get the correct value
        else
            target = ((4032/100) * target) + 3968;
    }
    else
        throw Exception_Servo("Invalid Target!\n");
}

int Servo::getChannels()
{      
}
