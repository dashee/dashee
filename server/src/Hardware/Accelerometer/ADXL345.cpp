#include <dashee/Hardware/Accelerometer/ADXL345.h>

using namespace dashee::Hardware;

/**
 * Create a new instance of a our Accelerometer.
 */
AccelerometerADXL345::AccelerometerADXL345() : Accelerometer()
{
    this->i2c = new dashee::I2C(1, 0x53);
}

/**
 * Update the g values by reading from the chip and storing locally.
 */
void AccelerometerADXL345::update()
{
    this->g = dashee::Point<float>(0.0f, 0.0f, 0.1f);
}

/**
 * Destroy the free store
 */
AccelerometerADXL345::~AccelerometerADXL345()
{
    delete this->i2c;
}

