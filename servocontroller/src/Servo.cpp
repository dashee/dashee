#include "Servo.h"

Servo::Servo(const char * dev)
{
    this->dev = dev;
    fd = open(this->dev, O_RDWR | O_NOCTTY);
    
    //Default the values
    std::fill_n(channels, 32, -1);

    if (fd == -1)
        throw Exception_Servo("Setting the device failed in Servo::Servo");
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
        throw Exception_Servo("Write failed in Servo::getChannel");
    
    if(read(fd,response,2) != 2)
        throw Exception_Servo("Read failed in Servo::getChannel");

    return (int)sqrt(response[0] + 256*response[1]);
}

int Servo::getTarget(const unsigned char channel)
{
    unsigned char command[2];
    command[0] = 0x90;
    command[1] = channel;

    if(write(this->fd, command, sizeof(command)) == -1)
        throw Exception_Servo("Write failed in Servo::getChannel");

    unsigned char response[2];
    if(read(fd,response,2) != 2)
        throw Exception_Servo("Read failed in Servo::getChannel");

    return response[0] + 256*response[1];
}

void Servo::setTarget(const unsigned char channel, const short int target)
{
    unsigned char command[4];
    command[0] = 0x84;
    command[1] = channel;
    command[2] = target & 127;
    command[3] = (target >> 7) & 127;

    if (write(this->fd, command, sizeof(command)) == -1)
        throw Exception_Servo("Write failed in Servo::setChannel");
    
    //Set the target
    channels[(short int)channel] = target;
}

int Servo::getChannels()
{      
}
