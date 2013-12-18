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
 * Class that holds the interface for our Accelerometer
 */
class dashee::Hardware::AccelerometerDummy 
    : public dashee::Hardware::Accelerometer
{
private:

protected:

    dashee::Coordinate<float> delta;

public:
    AccelerometerDummy();

    // Set the value of the delta
    void setDelta(dashee::Coordinate<float> delta);
    dashee::Coordinate<float> getDelta() const;

    // Return the value read
    dashee::Coordinate<float> read() const;
    void update();

    virtual ~AccelerometerDummy();
};

#endif

