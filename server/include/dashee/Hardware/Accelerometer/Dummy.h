/**
 * @file include/dashee/Hardware/Accelerometer/Dummy.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */
#ifndef DASHEE_HARDWARE_ACCELEROMETER_DUMMY_H_
#define DASHEE_HARDWARE_ACCELEROMETER_DUMMY_H_

#include <dashee/Hardware/Accelerometer.h>

namespace dashee
{
    namespace Hardware
    {
	class AccelerometerDummy;
    }
}

/**
 * Class that holds the interface for our Accelerometer.
 *
 * This dummy class helps replicate a strict environment so we can carry out 
 * testing, without outside disturbance.
 */
class dashee::Hardware::AccelerometerDummy 
    : public dashee::Hardware::Accelerometer
{
private:

protected:

    /**
     * The delta provides a way to set the delta value of an axis, 
     * during update. Helpful to make this class dynamic
     */
    dashee::Point<float> delta;

    /**
     * The maximum number any axis of a coordinate can read.
     *
     * This helpful variable reverses our delta values, when the MAX axis is 
     * reached, note in some cases this is not helpful so 0 represents no max.
     */
    static constexpr float MAX = 15.0f;

public:
    AccelerometerDummy();

    // Set the value of the delta
    void setDelta(dashee::Point<float> delta);
    dashee::Point<float> getDelta() const;

    // Update the sensor
    void update();

    // Destruct
    virtual ~AccelerometerDummy();
};

#endif
