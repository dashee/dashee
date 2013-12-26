#include "Hardware/Accelerometer/ADXL345.h"

using namespace dashee::test::Hardware;

/**
 * Create a new pointer to the dummy object
 */
void AccelerometerADXL345::setUp()
{
    this->accelerometer = new dashee::Hardware::AccelerometerADXL345();
}

/**
 * Test the default state of the loaded class
 */
void AccelerometerADXL345::testConstructDefault()
{

}

/**
 * Test the read function by calling read on the Accelerometer
 */
void AccelerometerADXL345::testReadAndUpdate()
{
    CPPUNIT_ASSERT(
	    this->accelerometer->read() 
	    == dashee::Point<float>(0.0f,0.0f,0.0f)
	);

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
 * Delete the pointer to the accelerometer
 */
void AccelerometerADXL345::tearDown()
{
    delete this->accelerometer;
}

