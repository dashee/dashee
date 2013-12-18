#include <dashee/Hardware/Accelerometer.h>

using namespace dashee::Hardware;

/**
 * Default our variables
 */
Accelerometer::Accelerometer()
{
    this->coordinate = dashee::Coordinate<float>();
}

/**
 * Do nothing destruct
 */
Accelerometer::~Accelerometer()
{
}
