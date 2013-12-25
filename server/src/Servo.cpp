#include <dashee/Servo.h>

using namespace dashee;

/** 
 * Initiate the Servo's defaults, fallback and current
 * structs to be set to 0, and also set the channel
 *
 * @param channel The channel that this servo belongs to
 * @param target The initial target to set the value
 */
Servo::Servo(const unsigned short int channel, unsigned short target)
    : SERVO_LOW(3968), SERVO_HIGH(8000)
{
    this->channel = channel;
    this->setTarget(target);
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

    this->target = target;
}
