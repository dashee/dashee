/**
 * @file include/dashee/Hardware.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */
#ifndef DASHEE_HARDWARE_ACCELEROMETER_H_
#define DASHEE_HARDWARE_ACCELEROMETER_H_

#include <dashee/Hardware.h>

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
template <class T> 
class dashee::Hardware::Accelerometer : public dashee::Hardware
{
private:
    Accelerometer();

protected:

public:

    virtual float read() = 0;

    virtual ~Accelerometer();
};

#endif
