#include "USB.h"

/**
 * The constructor of servo which takes in the device to open
 * usually the device is /dev/ttyACM0 but this could be different going from system to system
 *
 * @param (const char *)dev - The name of the device which will be open
 * @throw Exception_Servo - If device opening fails, an exception will be thrown
 */
Servo_USB::Servo_USB(const char * dev) : Servo(dev)
{
    fd = open(this->dev, O_RDWR | O_NOCTTY);

    if (fd == -1)
        throw Exception_Servo();
}

/**
 * Handler to close our @fd opened device
 */
Servo_USB::~Servo_USB()
{
    close(this->fd);    
}

/**
 * The Pololu board provides a error handling, This function is designed to 
 * get the last error from the Pololy Maestro USB Servo board, Note on retriving 
 * the error, the error is reset. So it is always a good idea to periodicly
 * pole the board.
 *
 * For performance reason we allow the user to worry about errors at his/hers perfernce
 *
 * The response is returned in a two byte represented by char, Only one bit is always set in
 * these two bytes, The error number is represeted by the nth bit set, For example
 * 
 *  00010000|00000000 - Will suggest Errornumber 3, as the erronumbering starts from 0
 * 
 * @reuturn short int - The integer response
 */
short int Servo_USB::getError()
{
    unsigned char command[] = { 0xA1 };
    unsigned char response[2];

    if (write(fd, command, sizeof(command)) == -1)
        throw Exception_Servo();
    
    if(read(fd,response,2) != 2)
        throw Exception_Servo();
    
    //TODO This needs to be fixed, its wrong at the moment
    return (short int)sqrt(response[0] + 256*response[1]);
}

/**
 * This command gets the target of a given channel.
 * To do this however we first need to write to the servo telling it that we want
 * the target value, of our given @channel. We then read from the board, which returns
 * the value in a 2 bytes which in collation represent one number.
 * 
 * The value's returned can range from 992 - 8000
 * 
 * The command to tell the servo that we want channel number requires two bytes the first
 * tells is we are using getTarget from the board, and the second tells it which channel
 * The byte to get is 0x90 as set by Pololu
 *
 * @param (const unsigned char)channel - The Channel to get
 * 
 * @throw Exception_Servo() - If a read write error occurs
 *
 * @return int - The value of the channel 
 */
unsigned short int Servo_USB::getTarget(const unsigned char channel)
{
    unsigned char command[2];
    command[0] = 0x90;
    command[1] = channel;

    if(write(this->fd, command, sizeof(command)) == -1)
        throw Exception_Servo();

    unsigned char response[2];
    if(read(fd,response,2) != 2)
        throw Exception_Servo("Invalid Target");

    return response[0] + 256*response[1];
}

/**
 * This sets the target of a channel given a servo. The target value is between
 * 0-100, the value is converted to the actual target using the calculateTarget()
 * function.
 *
 * Once we have a target value, we build the command. The command for the board is
 * represented in 4 bytes, where the first byte represent the set command, the second
 * represents the channel, and the 3rd and 4rth represent the value. Note that the 4th
 * and third byte have there Most significant byte set to 0.
 *
 * @param (const unsigned char)channel - The channel number represented in one byte
 * @paran (short int)target - Our target to set represented in 2 byte, with a value of 0-100
 *
 * @throw Exception_Servo - If writing to the board fails
 */
void Servo_USB::setTarget(const unsigned char channel, unsigned short int target)
{
    calculateTarget(target);
 
    unsigned char command[4];
    command[0] = 0x84;
    command[1] = channel;

    // Given an integer needs to be crammed into 2 bytes, with there MSB
    // Set to 0, we need to use 
    //    target & 01111111; to zero our MSB
    // 
    // Then shift the remaining bits and AND by 127
    //       (101010101 >> 7) & 011111111
    // Given us a 2 byte target number with there MSB cleared.
    command[2] = target & 127;
    command[3] = (target >> 7) & 127;

    if (write(this->fd, command, sizeof(command)) == -1)
        throw Exception_Servo();
}

/**
 * TODO finish the implimentation of this function
 */
int Servo_USB::getChannels()
{
    return 0;      
}
