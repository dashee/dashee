#include "Hardware/Accelerometer/Dummy.h"

using namespace dashee::test::Hardware;

/**
 * Create a new pointer to the dummy object
 */
void AccelerometerDummy::setUp()
{
    this->accelerometer = new dashee::Hardware::AccelerometerDummy();
}

/**
 * Test the default state of the loaded class
 */
void AccelerometerDummy::testDefaultLoad()
{

}

/**
 * Test the read function by calling read on the Accelerometer
 */
void AccelerometerDummy::testReadAndUpdate()
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
void AccelerometerDummy::testSetAndGetDelta()
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
void AccelerometerDummy::tearDown()
{
    delete this->accelerometer;
}
