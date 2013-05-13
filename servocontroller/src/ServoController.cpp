#include "ServoController.h"

/** 
 * This constructor sets our @dev variable, 
 * The dev variable is defined by param dev.
 * This constructer is initialized by derved clases
 *
 * @param (const char *)dev - The device name
 */
ServoController::ServoController(const char * dev)
{
    this->dev = dev;
}

/** 
 * Clean up our servos array using delete, and remove it from
 * our list
 */ 
ServoController::~ServoController()
{
    while(!servos.empty())
    {
        delete servos.back();
        servos.pop_back();
    }
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
unsigned short int ServoController::getTarget(const unsigned short int channel)
{
    if (channel >= this->size())
        throw Exception_ServoController_OutOfBound("Invalid Channel Number when trying to get.");

    return servos[channel]->getTarget();
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
void ServoController::setTarget(const unsigned short int channel, unsigned short int target)
{
    if (channel >= this->size())
        throw Exception_ServoController_OutOfBound("Invalid Channel Number when trying to set.");

    return servos[channel]->setTarget(target);
}

/** 
 * This function will return the size of @servos, it is a pass through
 * to the std::vector.size() function for the variable @servos
 *
 * @return unsigned int - Unsigned integral type
 */
unsigned int ServoController::size()
{
    return servos.size();
}
