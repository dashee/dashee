#include "Hardware/Accelerometer/ADXL345.h"

using namespace dashee::test::Hardware;

/**
 * Initialize our accelerometer class
 */
void AccelerometerADXL345::setUp()
{
    this->accelerometer = new dashee::Hardware::AccelerometerADXL345();
}

/**
 * Test the default state of the loaded class. This must always assume that the 
 * `g` value is set to 0 from the default constructor.
 */
void AccelerometerADXL345::testConstructDefault()
{
    CPPUNIT_ASSERT(
	    this->accelerometer->read() 
	    == dashee::Point<float>(0.0f,0.0f,0.0f)
	);
}

/**
 * Test the construction when a I2C device is passed through. The only assertion
 * we run is that the i2c object should be not null as the relationship is 
 * aggregate.
 */
void AccelerometerADXL345::testConstructI2C()
{
    // Delete existing accelerometer from setUp
    delete this->accelerometer;

    // Create and destroy a AccelerometerADXL345 object with I2C
    dashee::I2C * i2c = new dashee::I2C(1, 0x53);
    this->accelerometer = new dashee::Hardware::AccelerometerADXL345(i2c);
    delete this->accelerometer;

    // Make sure that I2C was not deleted
    CPPUNIT_ASSERT(i2c != NULL);

    // Free and reset for tear down
    delete i2c;
    this->accelerometer = new dashee::Hardware::AccelerometerADXL345();
}

/**
 * Test setting the range and getting the range values back from the server.
 * The values that can be set are 2, 4, 8 and 16 anything else is invalid
 * which is testing in testInvalidRange();
 */
void AccelerometerADXL345::testSetAndGetRange()
{
    // Check the initial value
    CPPUNIT_ASSERT(this->accelerometer->getRange() == 2);

    this->accelerometer->setRange(2);
    CPPUNIT_ASSERT(this->accelerometer->getRange() == 2);

    this->accelerometer->setRange(4);
    CPPUNIT_ASSERT(this->accelerometer->getRange() == 4);
    
    this->accelerometer->setRange(8);
    CPPUNIT_ASSERT(this->accelerometer->getRange() == 8);
    
    this->accelerometer->setRange(16);
    CPPUNIT_ASSERT(this->accelerometer->getRange() == 16);
}

/**
 * Test setting and getting the bandwidth, using enums instead of actual values
 */
void AccelerometerADXL345::testSetAndGetBandwidth()
{
    CPPUNIT_ASSERT(
	    this->accelerometer->getBandwidthRate() 
	    == dashee::Hardware::AccelerometerADXL345::BW_200
	);

    this->accelerometer->setBandwidthRate(
	    dashee::Hardware::AccelerometerADXL345::BW_0_10
	);
    CPPUNIT_ASSERT(
	    this->accelerometer->getBandwidthRate() 
	    == dashee::Hardware::AccelerometerADXL345::BW_0_10
	);
    
    this->accelerometer->setBandwidthRate(
	    dashee::Hardware::AccelerometerADXL345::BW_0_20
	);
    CPPUNIT_ASSERT(
	    this->accelerometer->getBandwidthRate() 
	    == dashee::Hardware::AccelerometerADXL345::BW_0_20
	);
}

/**
 * Test the read function by calling read on the Accelerometer.
 *
 * Given our initial `g` state is `[0,0,0]` post update we should at least
 * get Z coordinate to be approximately 9.8 so we can safely assume that after
 * the first update of our accelerometer we no longer are `[0,0,0]` but 
 * somewhere approximately `[0,0,9.8]`. This is of course assuming that we are 
 * not accelerating in the X or Y.
 *
 * I am not sure we can go further than the above simple testing otherwise 
 * unless ofcourse we can simulate the exact forces applied to our sensor.
 * 
 * Good luck with that!
 */
void AccelerometerADXL345::testReadAndUpdate()
{
    // Once updated the value of the accelerometer will not be the
    // constructed one, and run it twice just to be sure
    this->accelerometer->update();
    CPPUNIT_ASSERT(
	    this->accelerometer->read() 
	    != dashee::Point<float>(0.0f,0.0f,0.0f)
	);
    this->accelerometer->update();
    CPPUNIT_ASSERT(
	    this->accelerometer->read() 
	    != dashee::Point<float>(0.0f,0.0f,0.0f)
	);
}

/**
 * Null pointers to the I2C construct are not allowed
 */
void AccelerometerADXL345::testInvalidI2C()
{
    dashee::I2C * i2c = NULL;
    dashee::Hardware::AccelerometerADXL345 * temp 
	= new dashee::Hardware::AccelerometerADXL345(i2c);
    temp->update(); // Dummy so it does not complain about unused
}

/**
 * The accelerometer throws a custom exception when the range value is an 
 * invalid value sent to setRange()
 */
void AccelerometerADXL345::testInvalidRange()
{
    // This should throw dashee::Hardware::ExceptionAccelerometerADXL345
    this->accelerometer->setRange(7);
}

/**
 * An invalid bandwidth range should throw an exception
 */
void AccelerometerADXL345::testInvalidBandwidth()
{
    this->accelerometer->setBandwidthRate(
	    static_cast<dashee::Hardware::AccelerometerADXL345::BandwidthRate>
	    (2000)
	);
}

/**
 * Delete the pointer to the accelerometer
 */
void AccelerometerADXL345::tearDown()
{
    delete this->accelerometer;
}

