#include "Hardware/Accelerometer/Dummy.h"

/**
 * Create a new pointer to the dummy object
 */
void dashee::test::Hardware::AccelerometerDummy::setUp()
{
    this->accelerometer = new dashee::Hardware::AccelerometerDummy();
}

/**
 * Test the default state of the loaded class
 */
void dashee::test::Hardware::AccelerometerDummy::testDefaultLoad()
{

}

/**
 * Test the read function by calling read on the Accelerometer
 */
void dashee::test::Hardware::AccelerometerDummy::testReadAndUpdate()
{
    CPPUNIT_ASSERT(
	    this->accelerometer->read() 
	    == dashee::Coordinate<float>(0.0f,0.0f,0.0f)
	);

    // By default because delta is [0, 0, 0] the update should do nothing
    // and the values or read should stay stagnant
    this->accelerometer->update();
    CPPUNIT_ASSERT(
	    this->accelerometer->read() 
	    == dashee::Coordinate<float>(0.0f,0.0f,0.0f)
	);

    this->accelerometer->setDelta(dashee::Coordinate<float>(0.01, 0.01, 0.01));
    this->accelerometer->update();
    CPPUNIT_ASSERT(
	    this->accelerometer->read() 
	    == dashee::Coordinate<float>(0.01f,0.01f,0.01f)
	);
    
    this->accelerometer->update();
    CPPUNIT_ASSERT(
	    this->accelerometer->read() 
	    == dashee::Coordinate<float>(0.02f,0.02f,0.02f)
	);
}

/**
 * Test setting and getting of delta values
 */
void dashee::test::Hardware::AccelerometerDummy::testSetAndGetDelta()
{
    // Test the default value
    CPPUNIT_ASSERT(
	    this->accelerometer->getDelta() 
	    == dashee::Coordinate<float>(0.0f, 0.0f, 0.0f)
	);

    // Test setting to positive
    this->accelerometer->setDelta(dashee::Coordinate<float>(0.01, 0.01, 0.01));
    CPPUNIT_ASSERT(
	    this->accelerometer->getDelta() 
	    == dashee::Coordinate<float>(0.01f, 0.01f, 0.01f)
	);
    
    // Test setting negative values
    this->accelerometer->setDelta(
	    dashee::Coordinate<float>(-0.01f, -0.01f, -0.01f)
	);
    CPPUNIT_ASSERT(
	    this->accelerometer->getDelta() 
	    == dashee::Coordinate<float>(-0.01f, -0.01f, -0.01f)
	);
}

/**
 * Delete the pointer to the accelerometer
 */
void dashee::test::Hardware::AccelerometerDummy::tearDown()
{
    delete this->accelerometer;
}
