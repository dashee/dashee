#include <dashee/Hardware/Accelerometer.h>

using namespace dashee::Hardware;

/**
 * Default our variables
 */
Accelerometer::Accelerometer()
{
    this->g = dashee::Point<float>();
}

/**
 * Returns the last read values of the sensor
 *
 * @returns float value
 */ 
dashee::Point<float> Accelerometer::read() const
{
    return this->g;
}

/**
 * Do nothing destruct
 */
Accelerometer::~Accelerometer()
{
}
