/**
 * @file include/dashee/Hardware/Exception/Accelerometer.h
 * @author Shahmir Javaid
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_HARDWARE_EXCEPTION_ACCELEROMETER_ADXL345_H_
#define DASHEE_HARDWARE_EXCEPTION_ACCELEROMETER_ADXL345_H_

#include <dashee/Hardware/Exception/Accelerometer.h>

namespace dashee
{
    namespace Hardware
    {
        class ExceptionAccelerometerADXL345;
    }
}

class dashee::Hardware::ExceptionAccelerometerADXL345
    : public dashee::Hardware::ExceptionAccelerometer
{
public:
    explicit ExceptionAccelerometerADXL345() : ExceptionAccelerometer()
    {
    }
    explicit ExceptionAccelerometerADXL345(const int ec) 
	: ExceptionAccelerometer(ec)
    { 
    }
    explicit ExceptionAccelerometerADXL345(std::string msg) 
	: ExceptionAccelerometer(msg)
    { 
    }
};

#endif
