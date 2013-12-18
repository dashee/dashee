#include <dashee/Hardware/Accelerometer/Dummy.h>

using namespace dashee::Hardware;

/**
 * Do nothing construct
 */
AccelerometerDummy::AccelerometerDummy() : Accelerometer()
{
    this->delta = dashee::Coordinate<float>();
}

/**
 * Set the new delta value.
 *
 * @param delta the Delta coordinate
 */
void AccelerometerDummy::setDelta(dashee::Coordinate<float> delta)
{
    this->delta = delta;
}

/**
 * Get the existing delta value
 *
 * @returns Coordinate that the current delta is set to
 */
dashee::Coordinate<float> AccelerometerDummy::getDelta() const
{
    return this->delta;
}   

/**
 * Returns the last read values of the sensor
 *
 * @returns float value
 */ 
dashee::Coordinate<float> AccelerometerDummy::read() const
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
void AccelerometerDummy::update()
{
    this->coordinate = this->coordinate + this->delta;
    
    if (MAX != 0)
    {
	// Reverse the delta, if the coordinate is out of MAX range
	if (this->coordinate.getX() > MAX)
	    this->delta.setX(this->delta.getX() * -1);

	if (this->coordinate.getY() > MAX)
	    this->delta.setY(this->delta.getY() * -1);

	if (this->coordinate.getZ() > MAX)
	    this->delta.setZ(this->delta.getZ() * -1);
    }

}

/**
 * Do nothing destruct
 */
AccelerometerDummy::~AccelerometerDummy()
{
}
