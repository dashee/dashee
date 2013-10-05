#include <dashee/ServoController.h>

using namespace dashee;

/** 
 * Construct our ServoController.
 *
 * This constructor sets our `dev` variable, 
 * The dev variable is defined by param dev.
 * This constructer is initialized by derved clases, 
 * Also set the fallbackmode to false, in the begining
 *
 * @param dev - The device name
 */
ServoController::ServoController(const char * dev)
{
    this->dev = dev;
}

/** 
 * Destruct and cleanup.
 *
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
 * Set the target of a servo identified by channel.
 *
 * This sets the target of a channel given a servo. The target value is between
 * 0-100, the value is converted to the actual target using the calculateTarget()
 * function.
 *
 * Once we have a target value, we build the command. The command for the board is
 * represented in 4 bytes, where the first byte represent the set command, the second
 * represents the channel, and the 3rd and 4rth represent the value. Note that the 4th
 * and third byte have there Most significant byte set to 0.
 *
 * @param channel The channel number represented in one byte
 * @param target Our target to set represented in 2 byte, with a value of 0-100
 *
 * @throws ExceptionOutOfBounds If invalid servo is chosen
 */
void ServoController::setTarget(const unsigned short int channel, unsigned short int target)
{
    if (channel >= this->size())
        throw ExceptionOutOfBounds("Invalid Channel Number when trying to set.");

    return this->servos[channel]->setTarget(target);
}

/**
 * Get the target of a servo identified by channel.
 *
 * This command gets the target of a given channel.
 * To do this however we first need to write to the servo telling it that we want
 * the target value, of our given `channel`. We then read from the board, which returns
 * the value in a 2 bytes which in collation represent one number.
 * 
 * The value's returned can range from 992 - 8000
 * 
 * The command to tell the servo that we want channel number requires two bytes the first
 * tells is we are using getTarget from the board, and the second tells it which channel
 * The byte to get is 0x90 as set by Pololu
 *
 * @param channel The Channel to get
 * 
 * @throws ExceptionOutOfBounds If a read write error occurs
 *
 * @returns The target value of the channel 
 */
unsigned short int ServoController::getTarget(const unsigned short int channel)
{
    if (channel >= this->size())
        throw ExceptionOutOfBounds("Invalid Channel Number when trying to get.");

    return servos[channel]->getTarget();
}

/**
 * Set the default target for a given channel.
 *
 * This is a helper function which allows the use to
 * set the default value of a target.
 *
 * @param channel Servo channel number
 * @param target The value of the target
 *
 * @throws ExceptionOutOfBounds
 */
void ServoController::setTargetDefault(const unsigned short int channel, unsigned short int target)
{
    if (channel >= this->size())
        throw ExceptionOutOfBounds("Invalid Channel Number when trying to set default value.");

    this->servos[channel]->setTargetDefault(target);
}

/**
 * Return the Target default of a given channel.
 *
 * Go to the channel servo and return the TargetDefault value
 *
 * @param channel The channel to get the value of
 *
 * @return The default target value
 * 
 * @throws ExceptionServoControllerOutOfBound
 */
unsigned short int ServoController::getTargetDefault(const unsigned short int channel)
{
    if (channel >= this->size())
        throw ExceptionOutOfBounds("Invalid Channel Number when trying to set default value.");
    
    return this->servos[channel]->getTargetDefault();
}

/**
 * Set the fallbacks target for the given Channel.
 *
 * @param channel Servo channel number
 * @param target The target to set to
 *
 * @throws ExceptionServoControllerOutOfBound
 */
void ServoController::setTargetFallback(const unsigned short int channel, unsigned short int target)
{
    if (channel >= this->size())
        throw ExceptionOutOfBounds("Invalid Channel Number when trying to set default value.");

    this->servos[channel]->setTargetFallback(target);
}

/**
 * Get the fallback target value for the given Channel.
 *
 * @param channel The channel value to get
 *
 * @returns the fallback Target of the give channel
 *
 * @throws ExceptionServoControllerOutOfBound
 */
unsigned short int ServoController::getTargetFallback(const unsigned short int channel)
{
    if (channel >= this->size())
        throw ExceptionOutOfBounds("Invalid Channel Number when trying to set default value.");

    return this->servos[channel]->getTargetFallback();
}
    
/**
 * Set the Servo::fallbacksEnabled for a given channel.
 * 
 * Helpfull passthrough to modify the Servo::fallbackEnabled value
 * for the given servo, identified by @p channel.
 *
 * @param channel Servo channel number
 * @param enabled The value
 *
 * @throws ExceptionOutOfBounds
 */
void ServoController::setTargetFallbackEnabled(const unsigned short int channel, bool enabled)
{
    if (channel >= this->size())
        throw ExceptionOutOfBounds("Invalid Channel Number when trying to set default value.");

    this->servos[channel]->setTargetFallbackEnabled(enabled);
}

/**
 * Get the Fallback Enabled value of the given channel.
 *
 * @param channel The channel in question
 *
 * @return boolean representing the value
 * @retval TRUE allowed to fallback
 * @retval FALSE not allowed to fallback
 *
 * @throws ExceptionOutOfBounds
 */
bool ServoController::getTargetFallbackEnabled(const unsigned short int channel)
{
    if (channel >= this->size())
        throw ExceptionOutOfBounds("Invalid Channel Number when trying to set default value.");

    return this->servos[channel]->getTargetFallbackEnabled();
}

/** 
 * Get the size of Servo's.
 *
 * This function will return the size of @p servos, it is a pass through
 * to the std::vector.size() function for the variable @p servos
 *
 * @return The number of servos in ServoController::servos
 */
unsigned int ServoController::size() const
{
    return this->servos.size();
}

/** 
 * Perform the fallback.
 *
 * Given the current state of @p fallbackmode, we iterate
 * through all servo's and set them to fallback mode, If
 * we have already fallen back then the flag should be true
 * in this case dont do any thing.
 *
 * Turn @p fallbackmode to true at the end
 */
void ServoController::fallback()
{
    for (unsigned int x = 0; x < this->servos.size(); x++)
    {
        servos[x]->fallback();
    }
}

/** 
 * Perform the revert.
 *
 * Given the current state of @p fallbackmode, we iterate
 * through all servo's and revert them to there original 
 * position. At the end @p fallbackmode is set to false, as
 * we have reverted
 */
void ServoController::revert()
{
    for (unsigned int x = 0; x < this->servos.size(); x++)
    {
        this->servos[x]->revert();
    }
}
