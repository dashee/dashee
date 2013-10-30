#include <dashee/Servo.h>

using namespace dashee;

/** 
 * Initiate the Servo's defaults, fallback and current
 * structs to be set to 0, and also set the channel
 *
 * @param channel - The channel that this servo belongs to
 */
Servo::Servo(const unsigned short int channel)
    : SERVO_LOW(3968), SERVO_HIGH(8000)
{
    this->channel = channel;
}
