#include <dashee/Hardware/Accelerometer/ADXL345.h>

using namespace dashee::Hardware;

/**
 * Create a new instance of a our Accelerometer.
 */
AccelerometerADXL345::AccelerometerADXL345() : Accelerometer()
{
    this->isI2CAllocatedInternally = false;
    this->i2c = new dashee::I2C(1, 0x53);
}

/**
 * This builds the Accelerometer with an existing I2C class. In this case the 
 * i2c deletion is not handled by the AccelerometerADXL345 class. To determine 
 * this we use the isI2CAllocatedInternally and set it to true, which is checked
 * by the destructor on deleting the object.
 *
 * @param i2c The I2C handler to the correct device
 *
 * @throws ExceptionNullPointer The value of I2C was NULL
 */
AccelerometerADXL345::AccelerometerADXL345(dashee::I2C * i2c)
{
    if (i2c == NULL)
	throw dashee::ExceptionNullPointer("I2c should be good");

    this->isI2CAllocatedInternally = false;
    this->i2c = i2c;
}

/**
 * Update the g values by reading from the chip and storing locally.
 */
void AccelerometerADXL345::update()
{
    this->g = dashee::Point<float>(0.0f, 0.0f, 0.1f);
}

/**
 * Destroy the free store memory only if I2C was internally allocated
 */
AccelerometerADXL345::~AccelerometerADXL345()
{
    if (isI2CAllocatedInternally)
	delete this->i2c;
}

