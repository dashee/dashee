#include <dashee/Hardware/Accelerometer/ADXL345.h>

using namespace dashee::Hardware;

/**
 * Create a new instance of a our Accelerometer.
 */
AccelerometerADXL345::AccelerometerADXL345() : Accelerometer()
{
    this->isI2CAllocatedInternally = false;
    this->i2c = new dashee::I2C(1);
    
    this->init();
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

    this->init();
}

/**
 * A simple init function used by all constructors. Helpful to put all generic
 * initialization in one place
 */
void AccelerometerADXL345::init()
{
    this->i2c->setSlaveAddress(0x53);
    this->setRange(2);
}

/**
 * Set the range of the device.
 *
 * @param range The range to set to
 *
 * @throws ExceptionAccelerometerADXL345 If the range is invalid
 */
void AccelerometerADXL345::setRange(const unsigned short int range)
{
    unsigned char range_byte;

    switch (range)
    {
	case 2:
	    range_byte = 0x00;
	    break;
	case 4:
	    range_byte = 0x01;
	    break;
	case 8:
	    range_byte = 0x02;
	    break;
	case 16:
	    range_byte = 0x03;
	    break;
	default:
	    throw ExceptionAccelerometerADXL345(
		    "Invalid range " + dashee::itostr(range)
		);
	    break;
    }

    std::vector<unsigned char> buffer;

    this->i2c->read(REGISTER_DATA_FORMAT, &buffer, 1);

    buffer[0] = (buffer[0] & ~0x3) | (range_byte);

    this->i2c->write(REGISTER_DATA_FORMAT, &buffer, 1);
}

/**
 * Get the value of the range itself from the DATA_FORMAT register.
 *
 * @returns the value of range
 * 
 * @throws ExceptionAccelerometerADXL345 If an invalid range is returned
 */
unsigned short int AccelerometerADXL345::getRange() const
{
    std::vector<unsigned char> buffer;
    this->i2c->read(REGISTER_DATA_FORMAT, &buffer, 1);
    unsigned char reg_range = 0x03 & buffer[0];

    // Return the reg_range if it is within the known values
    switch (reg_range)
    {
	case 0x00:
	    return 2u;
	    break;
	case 0x01:
	    return 4u;
	    break;
	case 0x02: 
	    return 8u;
	    break;
	case 0x03:
	    return 16u;
	    break;
	default:
	    throw ExceptionAccelerometerADXL345(
		    "Invalid range came back from the register"
		);
	    break;
    }

    // Should never happen
    return 0u;
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

