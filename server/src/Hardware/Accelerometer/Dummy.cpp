#include <dashee/Hardware/Accelerometer/Dummy.h>

/**
 * Do nothing construct
 */
dashee::Hardware::AccelerometerDummy::AccelerometerDummy()
    : dashee::Hardware::Accelerometer()
{
    this->delta = dashee::Coordinate<float>();
}

/**
 * Set the new delta value.
 *
 * @param delta the Delta coordinate
 */
void dashee::Hardware::AccelerometerDummy::setDelta(
	dashee::Coordinate<float> delta
    )
{
    this->delta = delta;
}

/**
 * Get the existing delta value
 *
 * @returns Coordinate that the current delta is set to
 */
dashee::Coordinate<float> dashee::Hardware::AccelerometerDummy::getDelta() const
{
    return this->delta;
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
 * Update the Accelerometer.
 *
 * The dummy Accelerometer updates the accelerometer from the delta value
 * the delta values are reset when the actual value of the accelerometer reaches
 * the max
 */
void dashee::Hardware::AccelerometerDummy::update()
{
    this->coordinate = this->coordinate + this->delta;
}

/**
 * Do nothing destruct
 */
dashee::Hardware::AccelerometerDummy::~AccelerometerDummy()
{

}
