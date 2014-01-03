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
void AccelerometerDummy::testConstructDefault()
{

}

/**
 * Test the read function by calling read on the Accelerometer
 */
void AccelerometerDummy::testReadAndUpdate()
{
    CPPUNIT_ASSERT(
	    this->accelerometer->read() 
	    == dashee::Point<double>(0.0,0.0,0.0)
	);

    // By default because delta is [0, 0, 0] the update should do nothing
    // and the values or read should stay stagnant
    this->accelerometer->update();
    CPPUNIT_ASSERT(
	    this->accelerometer->read() 
	    == dashee::Point<double>(0.0,0.0,0.0)
	);

    this->accelerometer->setDelta(dashee::Point<double>(0.01, 0.01, 0.01));
    this->accelerometer->update();
    CPPUNIT_ASSERT(
	    this->accelerometer->read() 
	    == dashee::Point<double>(0.01,0.01,0.01)
	);
    
    this->accelerometer->update();
    CPPUNIT_ASSERT(
	    this->accelerometer->read() 
	    == dashee::Point<double>(0.02,0.02,0.02)
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
	    == dashee::Point<double>(0.0, 0.0, 0.0)
	);

    // Test setting to positive
    this->accelerometer->setDelta(dashee::Point<double>(0.01, 0.01, 0.01));
    CPPUNIT_ASSERT(
	    this->accelerometer->getDelta() 
	    == dashee::Point<double>(0.01, 0.01, 0.01)
	);
    
    // Test setting negative values
    this->accelerometer->setDelta(
	    dashee::Point<double>(-0.01, -0.01, -0.01)
	);
    CPPUNIT_ASSERT(
	    this->accelerometer->getDelta() 
	    == dashee::Point<double>(-0.01, -0.01, -0.01)
	);
}

/**
 * Delete the pointer to the accelerometer
 */
void AccelerometerDummy::tearDown()
{
    delete this->accelerometer;
}
