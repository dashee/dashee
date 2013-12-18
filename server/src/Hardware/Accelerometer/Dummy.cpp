#include <dashee/Hardware/Accelerometer/Dummy.h>

/**
 * Do nothing construct
 */
dashee::Hardware::AccelerometerDummy::AccelerometerDummy()
    : dashee::Hardware::Accelerometer()
{
}

/**
 * Returns the last read values of the sensor
 *
 * @returns float value
 */ 
dashee::Coordinate<float> dashee::Hardware::AccelerometerDummy::read() const
{
    return this->coordinate;
}

/**
 * Do nothing destruct
 */
dashee::Hardware::AccelerometerDummy::~AccelerometerDummy()
{

}

