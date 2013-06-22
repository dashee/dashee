#include "ServoController.h"

/** 
 * This constructor sets our @dev variable, 
 * The dev variable is defined by param dev.
 * This constructer is initialized by derved clases, 
 * Also set the fallbackmode to false, in the begining
 *
 * @param dev - The device name
 */
ServoController::ServoController(const char * dev)
{
    this->dev = dev;

    fallbackmode = false;
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
 * @param channel - The Channel to get
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
 * @param channel - The channel number represented in one byte
 * @paran target - Our target to set represented in 2 byte, with a value of 0-100
 *
 * @throw Exception_Servo - If writing to the board fails
 */
void ServoController::setTarget(const unsigned short int channel, unsigned short int target)
{
    if (fallbackmode)
        revert();

    if (channel >= this->size())
        throw Exception_ServoController_OutOfBound("Invalid Channel Number when trying to set.");

    return servos[channel]->setTarget(target);
}

/**
 * Set the default Target values of a given Channel
 *
 * @param channel - Servo channel number
 * @param target - The value of the target
 *
 * @throws Exception_ServoController_OutOfBound
 */
void ServoController::setTargetDefault(const unsigned short int channel, unsigned short int target)
{
    if (channel >= this->size())
        throw Exception_ServoController_OutOfBound("Invalid Channel Number when trying to set default value.");

    servos[channel]->setTargetDefault(target);
}

/**
 * Set the fallbacks.target for the given Channel
 *
 * @param channel - Servo channel number
 * @param target - The target to set to
 *
 * @throws Exception_ServoController_OutOfBound
 */
void ServoController::setTargetFallback(const unsigned short int channel, unsigned short int target)
{
    if (channel >= this->size())
        throw Exception_ServoController_OutOfBound("Invalid Channel Number when trying to set default value.");

    servos[channel]->setTargetFallback(target);
}

/**
 * Set the fallbacksEnabled.target for a given channel
 *
 * @param channel - Servo channel number
 * @param enabled - The value
 *
 * @throws Exception_ServoController_OutOfBound
 */
void ServoController::setTargetFallbackEnabled(const unsigned short int channel, bool enabled)
{
    if (channel >= this->size())
        throw Exception_ServoController_OutOfBound("Invalid Channel Number when trying to set default value.");

    servos[channel]->setTargetFallbackEnabled(enabled);
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

/** 
 * Given the current state of @fallbackmode, we iterate
 * through all servo's and set them to fallback mode, If
 * we have already fallen back then the flag should be true
 * in this case dont do any thing.
 *
 * turn @fallbackmode to true at the end
 */
void ServoController::fallback()
{
    if (fallbackmode) { return; }

    for (unsigned int x = 0; x < servos.size(); x++)
        servos[x]->fallback();

    fallbackmode = true;

    Log::warning(2, "Fallback mode activated.");
}

/** 
 * Given the current state of @fallbackmode, we iterate
 * through all servo's and revert them to there original 
 * position. At the end @fallbackmode is set to false, as
 * we have reverted
 */
void ServoController::revert()
{
    for (unsigned int x = 0; x < servos.size(); x++)
    {
        try
        {
            servos[x]->revert();
        }
        catch (Exception_Servo e)
        {
            //Dont throw here, because Invalid channels 
            //should not be prevent others from reverting
            Log::warning(1, "servo[%d]->revert() threw an exception.", x);
            Log::warning(1, e.what());
        }
    }
    
    fallbackmode = false;
}
