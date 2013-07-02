#include "UART.h"

/**
 * This constructor will get the fd of the servo device that is open by 
 * its parrent ServoController_UART class. The fd is used to talk to the 
 * servo
 *
 * @param (const char *)dev - The name of the device which will be open
 * @throw Exception_Servo - If device opening fails, an exception will be thrown
 */
Servo_UART::Servo_UART(int * fd, const unsigned short int channel) : Servo(channel)
{
    this->fd = fd;
}

/**
 * destruct
 */
Servo_UART::~Servo_UART()
{
}

/**
 * This command gets the target of a given channel.
 * To do this however we first need to write to the servo telling it that we want
 * the target value, of our given @channel. We then read from the board, which returns
 * the value in a 2 bytes which in collation represent one number.
 * 
 * The value's returned can range from 992 - 8000
 * 
 * The command to tell the servo that we want channel number requires four bytes 
 *  1st byte - Static protocoal value always set to 0xAA
 *  2nd byte - The device number
 *  3rd byte - The command to set target it is 0x10
 *  4th byte - The channel
 *
 * @throw Exception_Servo() - If a read write error occurs
 *
 * @return int - The Target value of a channel 
 */
unsigned short int Servo_UART::getTarget()
{
    unsigned char command[4];
    command[0] = 0xAA;
    command[1] = 0xC;
    command[2] = 0x10;
    command[3] = (char)this->channel;

    if(write(*this->fd, command, sizeof(command)) == -1)
        throw Exception_Servo("Servo_UART::getTarget write failed");

    unsigned char response[2];
    
    // Go through and read each byte by byte
    for (int n = 0, total = 0; n < 2; total++)
    {
        if (total > 10)
            throw Exception_Servo("Reading getError, ran more than 10 times");

        int ec = read(*this->fd, response+n, 1);

        // the ec came back with read error, lets not continue
        if(ec < 0)
            throw Exception_Servo("read failed in Servo_UART::getTarget");

        // the ec came back with 0, which means sleep and try again
        if (ec == 0)
            continue;
        
        // nth response was set, lets set the next one
        n++;
    }

    return response[0] + 256*response[1];
}

/**
 * This function will talk to our board and set the specific channel to the required byte
 *
 * The command to tell the servo that we want to set channel number requires 6 bytes 
 *  1st byte - Static protocoal value always set to 0xAA
 *  2nd byte - The device number
 *  3rd byte - The command to set target it is 0x10
 *  4th byte - The channel
 *  5th byte - The data first byte
 *  6th byte - The data second byte
 *
 * @param (short int)target - Our target to set represented in 2 byte, with a value of 0-100
 *
 * @throw Exception_Servo - If writing to the board fails
 */
void Servo_UART::setTarget(unsigned short int target)
{
    // Convert the percentage target value
    // to Servo controller target value
    PercentageToTarget(target);
 
    unsigned char command[6];
    command[0] = 0xAA;
    command[1] = 0xC;
    command[2] = 0x04;
    command[3] = this->channel;

    // Given an integer needs to be crammed into 2 bytes, with there MSB
    // Set to 0, we need to use 
    //    target & 01111111; to zero our MSB
    // 
    // Then shift the remaining bits and AND by 127
    //       (101010101 >> 7) & 011111111
    // Given us a 2 byte target number with there MSB cleared.
    command[4] = target & 127;
    command[5] = (target >> 7) & 127;

    if (write(*this->fd, command, sizeof(command)) == -1)
        throw Exception_Servo("Servo_UART::setTarget write failed");
}
