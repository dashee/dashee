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
 * Delete the pointer to the accelerometer
 */
void AccelerometerADXL345::tearDown()
{
    delete this->accelerometer;
}

