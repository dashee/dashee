#include <dashee/Hardware/Accelerometer/Dummy.h>

using namespace dashee::Hardware;

/**
 * Do nothing construct
 */
AccelerometerDummy::AccelerometerDummy() : Accelerometer()
{
    this->delta = dashee::Point<double>();
}

/**
 * Set the new delta value.
 *
 * @param delta the Delta coordinate
 */
void AccelerometerDummy::setDelta(dashee::Point<double> delta)
{
    this->delta = delta;
}

/**
 * Get the existing delta value
 *
 * @returns Point that the current delta is set to
 */
dashee::Point<double> AccelerometerDummy::getDelta() const
{
    return this->delta;
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
    this->g = this->g + this->delta;
    
    if (MAX != 0)
    {
	// Reverse the delta, if the g is out of MAX range
	if (this->g.getX() > MAX)
	    this->delta.setX(this->delta.getX() * -1.0);

	if (this->g.getY() > MAX)
	    this->delta.setY(this->delta.getY() * -1.0);

	if (this->g.getZ() > MAX)
	    this->delta.setZ(this->delta.getZ() * -1.0);
    }
}

/**
 * Do nothing destruct
 */
AccelerometerDummy::~AccelerometerDummy()
{
}
