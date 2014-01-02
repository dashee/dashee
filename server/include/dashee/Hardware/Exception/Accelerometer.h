/**
 * @file include/dashee/Hardware/Exception/Accelerometer.h
 * @author Shahmir Javaid
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_HARDWARE_EXCEPTION_ACCELEROMETER_H_
#define DASHEE_HARDWARE_EXCEPTION_ACCELEROMETER_H_

#include <dashee/Hardware/Exception.h>

namespace dashee
{
    namespace Hardware
    {
        class ExceptionAccelerometer;
    }
}

class dashee::Hardware::ExceptionAccelerometer
    : public dashee::Hardware::Exception
{
public:
    explicit ExceptionAccelerometer() : Exception()
    {
    }
    explicit ExceptionAccelerometer(const int ec) : Exception(ec)
    { 
    }
    explicit ExceptionAccelerometer(std::string msg) : Exception(msg)
    { 
    }
};

#endif
