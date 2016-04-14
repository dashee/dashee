#include <dashee/Hardware/Accelerometer.h>

using namespace dashee::Hardware;

/**
 * Default our variables
 */
Accelerometer::Accelerometer()
{
    this->g = dashee::Point<double>();
}

/**
 * Returns the last read values of the sensor
 *
 * @returns float value
 */ 
dashee::Point<double> Accelerometer::read() const
{
    return this->g;
}

/**
 * Do nothing destruct
 */
Accelerometer::~Accelerometer()
{
}
