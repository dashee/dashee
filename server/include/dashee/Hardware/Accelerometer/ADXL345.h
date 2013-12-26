/**
 * @file include/dashee/Hardware/Accelerometer/ADXL345.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */
#ifndef DASHEE_HARDWARE_ACCELEROMETER_ADXL345_H_
#define DASHEE_HARDWARE_ACCELEROMETER_ADXL345_H_

#include <dashee/I2C.h>
#include <dashee/Hardware/Accelerometer.h>

namespace dashee
{
    namespace Hardware
    {
	class AccelerometerADXL345;
    }
}

/**
 * Control interface for the ADXL345 chip.
 *
 * You can find out in detail about the chip at http://goo.gl/RyfX6J where it 
 * holds all the information about the register. This class does not provide all
 * the functionality help by the chip, only those which is used by our system.
 * Feel free to add your own.
 *
 * Usage:
 *
 *     Coordinate<float> g;
 *     AccelerometerADXL345 accelerometer;
 *
 *     while(true)
 *     {
 *         accelerometer.update();
 *         g = accelerometer.read();
 *     }
 */
class dashee::Hardware::AccelerometerADXL345 
    : public dashee::Hardware::Accelerometer
{
private:

protected:

    /**
     * Interface to control our device.
     */ 
    dashee::I2C * i2c;

public:

    // Construct
    AccelerometerADXL345();
    //AccelerometerADXL345(dashee::I2C * i2c);
    //AccelerometerADXL345(const AccelerometerADXL345 & rhs);

    // Assignment operation
    //AccelerometerADXL345& operator=(const AccelerometerADXL345 & rhs);

    // Update the sensor
    void update();

    // Destruct
    virtual ~AccelerometerADXL345();
};

#endif
