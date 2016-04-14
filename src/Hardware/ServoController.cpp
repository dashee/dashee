#include <dashee/Hardware/ServoController.h>

using namespace dashee::Hardware;

/** 
 * Construct our ServoController.
 *
 * This constructor sets our `dev` variable, 
 * The dev variable is defined by param dev.
 * This constructor is initialized by derived class, 
 * Also set the fall-back-mode to false, in the beginning
 *
 * @param dev - The device name
 */
ServoController::ServoController(const char * dev) : dev(dev)
{
}

/**
 * Set the target of a servo identified by channel.
 *
 * @param channel The channel number represented in one byte
 * @param target Our target to set represented in 2 byte, with a value of 0-100
 *
 * @throws ExceptionOutOfBounds If invalid servo is chosen
 */
void ServoController::setTarget(
        const unsigned short int channel, 
        unsigned short int target
    )
{
    if (channel >= this->size())
        throw ExceptionOutOfBounds(
                "Invalid Channel " + 
                dashee::itostr(channel) + 
                " when trying to set."
            );

    return this->servos[channel]->setTarget(target);
}

/**
 * Get the target of a servo identified by channel.
 *
 * @param channel The Channel to get
 * 
 * @throws ExceptionOutOfBounds If a read write error occurs
 *
 * @returns The target value of the channel 
 */
unsigned short int ServoController::getTarget(
        const unsigned short int channel
    ) const
{
    if (channel >= this->size())
        throw ExceptionOutOfBounds(
                "Invalid Channel " + 
                dashee::itostr(channel) + 
                " when trying to get target."
            );

    return this->servos[channel]->getTarget();
}

/**
 * Return the pointer to the servo given by channel
 * 
 * @param channel The Channel of the servo to get
 * 
 * @throws ExceptionOutOfBounds If a read write error occurs
 *
 * @returns The pointer to the servo
 */
Servo & ServoController::getServo(const unsigned short int channel)
{
    if (channel >= this->size())
        throw ExceptionOutOfBounds(
                "Invalid Channel " + 
                dashee::itostr(channel) + 
                " when trying to get servo."
            );

    return *this->servos[channel];
}

/**
 * Helpful [] operator to get a servo
 *
 * @param channel The channel number to get
 *
 * @return The Servo it self
 */
Servo & ServoController::operator[](const size_t channel)
{
    if (channel >= this->size())
        throw ExceptionOutOfBounds(
                "Invalid Channel " + 
                dashee::itostr(channel) + 
                " when trying to get servo[]."
            );

    return *this->servos[channel];
}

/**
 * Returns the flag representing weather a servo is inverted or not.
 *
 * @param channel The channel to check
 */
bool ServoController::isInverted(const unsigned short int channel) const
{
    if (channel >= this->size())
        throw ExceptionOutOfBounds(
                "Invalid Channel " + 
                dashee::itostr(channel) + 
                " when trying check isInverted."
            );

    return this->servos[channel]->isInverted();
}

/**
 * Invert the value.
 *
 * @param channel The channel to invert
 * @param value enable or disable invert
 */ 
void ServoController::invert(const unsigned short int channel, const bool value)
{
    if (channel >= this->size())
        throw ExceptionOutOfBounds(
                "Invalid Channel " + 
                dashee::itostr(channel) + 
                " when trying to invert."
            );

    return this->servos[channel]->invert(value);
}

/** 
 * Get the size of Servo's.
 *
 * This function will return the size of @p servos, it is a pass through
 * to the std::vector.size() function for the variable @p servos
 *
 * @return The number of servos in ServoController::servos
 */
size_t ServoController::size() const
{
    return this->servos.size();
}

/** 
 * Destruct and cleanup.
 *
 * Clean up our servos array using delete, and remove it from
 * our list
 */ 
ServoController::~ServoController()
{
    while(!this->servos.empty())
    {
        delete servos.back();
        this->servos.pop_back();
    }
}
