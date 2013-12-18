/**
 * @file include/dashee/Hardware/Accelerometer.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */
#ifndef DASHEE_HARDWARE_ACCELEROMETER_H_
#define DASHEE_HARDWARE_ACCELEROMETER_H_

#include <dashee/Coordinate.h>

namespace dashee
{
    namespace Hardware
    {
	class Accelerometer;
    }
}

/**
 * Class that holds the interface for our Accelerometer
 */
class dashee::Hardware::Accelerometer
{
private:

protected:

    /**
     * The coordinates which hold the gravitational pull in three axis
     */
    dashee::Coordinate<float> coordinate;
    Accelerometer();

public:

    // Return the value of read
    virtual dashee::Coordinate<float> read() const = 0;

    virtual ~Accelerometer();
};

#endif

