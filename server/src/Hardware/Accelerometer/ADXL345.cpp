#include <dashee/Hardware/Accelerometer/ADXL345.h>

using namespace dashee::Hardware;

//const static float AccelerometerADXL345::SCALE = 0.00390625f;

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
    this->dataBuffer = std::vector<unsigned char>(6, 0);
    this->i2c->setSlaveAddress(0x53);
    this->setRange(2);
    this->setBandwidthRate(BW_200);
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
 * Set the bandwidth range of the BW_RATE register
 *
 * @param rate the Rate to set to
 *
 * @throws ExceptionAccelerometerADXL345 If the rate value is wrong
 */
void AccelerometerADXL345::setBandwidthRate(
	const BandwidthRate rate
    )
{
    // Read the old values into the buffer.
    std::vector<unsigned char> buffer(1, 0);
    this->i2c->read(REGISTER_BW_RATE, &buffer, 1);

    switch (rate)
    {
	// Set the new rate value, only in the 3:0 bit of the byte where the 7:4
	// bits are carried from their last position.
	case BW_0_10:
	case BW_0_20:
	case BW_0_39:
	case BW_0_78:
	case BW_1_56:
	case BW_3_13:
	case BW_6_25:
	case BW_12_5:
	case BW_25:
	case BW_50:
	case BW_100:
	case BW_200:
	case BW_400:
	case BW_800:
	case BW_1600:
	case BW_3200:
	    buffer[0] = (buffer[0] & 0xF0) | static_cast<unsigned char>(rate);
	    break;
	default:
	    throw ExceptionAccelerometerADXL345(
		    "Invalid Rate type when trying to set Bandwidth"
		);
	    break;
    }
    
    // Write the new values to our device
    this->i2c->write(REGISTER_BW_RATE, &buffer, 1);
}

/**
 * Return the rate set on the board currently. 
 *
 * The rate is set in the REGSITER_BW_RATE register address, and the rate values
 * are represented in 3:0 bit in the one byte returned. So our return blanks out
 * all values in the 7:4 bit.
 *
 * No checks are made to ensure the value returned is correct. I can't think of
 * a case where a check needs to be made so if it does please add it.
 *
 * @returns BandwidthRate the rate of Hertz currently set on the board.
 */
AccelerometerADXL345::BandwidthRate AccelerometerADXL345::getBandwidthRate() 
    const
{
    std::vector<unsigned char> buffer(1, 0);
    this->i2c->read(REGISTER_BW_RATE, &buffer, 1);

    // Return only the values which represent the enum.
    return static_cast<BandwidthRate>(buffer[0] & 0x0F);
}

/**
 * Update the g values by reading from the chip and storing locally.
 */
void AccelerometerADXL345::update()
{
    // Read 6 bytes from the data register, starting from DATAX0 and all the way
    // to DATAZ1
    this->i2c->read(REGISTER_DATAX0, &this->dataBuffer, 6);
    
    int16_t valX = dataBuffer[0] | (dataBuffer[1] << 8);
    int16_t valY = dataBuffer[2] | (dataBuffer[3] << 8);
    int16_t valZ = dataBuffer[4] | (dataBuffer[5] << 8);

    this->g = dashee::Point<float>(
	    static_cast<float>(valX), 
	    static_cast<float>(valY), 
	    static_cast<float>(valZ)
	);
}

/**
 * Destroy the free store memory only if I2C was internally allocated
 */
AccelerometerADXL345::~AccelerometerADXL345()
{
    if (isI2CAllocatedInternally)
	delete this->i2c;
}

