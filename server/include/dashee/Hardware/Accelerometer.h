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

#include <dashee/Point.h>

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
     * The g coordinates.
     *
     * The coordinates which hold the last value of the gravitational pull in 
     * three axis.
     */
    dashee::Point<float> g;

    // Default the in class variables
    Accelerometer();

public:

    // Return the value of read from the sensor
    virtual dashee::Point<float> read() const;

    // Update the value of this class from the sensor
    virtual void update() = 0;

    // Do nothing
    virtual ~Accelerometer();
};

#endif

