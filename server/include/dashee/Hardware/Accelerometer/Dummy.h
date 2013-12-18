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

public:
    AccelerometerDummy();

    // Return the value read
    dashee::Coordinate<float> read() const;

    virtual ~AccelerometerDummy();
};

#endif

