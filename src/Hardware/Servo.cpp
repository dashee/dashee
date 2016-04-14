#include <dashee/Hardware/Servo.h>

using namespace dashee::Hardware;

/** 
 * Initiate the Servo's defaults, fallback and current
 * struct to be set to 0, and also set the channel
 *
 * @param channel The channel that this servo belongs to
 * @param target The initial target to set the value
 */
Servo::Servo(const unsigned short int channel)
    : target(0), inverted(false), SERVO_LOW(3968), SERVO_HIGH(8000)
{
    this->channel = channel;
}

/** 
 * Set the target value
 *
 * @param target The value to set
 *
 * @throws ExceptionServo
 */
void Servo::setTarget(unsigned short int target)
{
    if (target > 255)
        throw ExceptionServo(
                "Target '" + 
                dashee::itostr(target) + 
                "' is invalid"
            );

    if (this->inverted)
        this->setPhysicalTarget(
            static_cast<unsigned short int>((target - 255) * -1)
        );
    else
        this->setPhysicalTarget(target);

    this->target = target;
}

/**
 * Get the target value
 *
 * @param fromcache To be fast a helpful fromcache value is set
 *
 * @returns the value of the servo
 */
unsigned short int Servo::getTarget(const bool fromcache)
{
    if (fromcache)
        return this->target;

    unsigned short int target = this->getPhysicalTarget();

    if (inverted)
        return static_cast<unsigned short int>((target - 255) * -1);
        
    return target;
}

/**
 * Returns indicating inverted status
 *
 * @returns the boolean value of inverted or not
 */
bool Servo::isInverted() const
{
    return inverted;
}

/**
 * Set the inverted value. Also flip the target value
 *
 * @param inverted the value to set
 */
void Servo::invert(const bool inverted)
{
    this->target = static_cast<unsigned short int>((this->target - 255) * -1);
    this->inverted = inverted;
}

/**
 * Destruct the servo
 */ 
Servo::~Servo()
{
}
