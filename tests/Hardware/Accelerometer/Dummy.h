/**
 * @file tests/Hardware/Accelerometer/Dummy.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_TEST_HARDWARE_ACCELEROMETER_DUMMY_H_
#define DASHEE_TEST_HARDWARE_ACCELEROMETER_DUMMY_H_

#include "Hardware/Accelerometer.h"
#include <dashee/Hardware/Accelerometer/Dummy.h>

/*
 * Set the namespace
 */
namespace dashee
{
    namespace test
    {
        namespace Hardware
        {
            class AccelerometerDummy;
        }
    }
}

/**
 * Test the Accelerometer Dummy class
 */
class dashee::test::Hardware::AccelerometerDummy
    : public dashee::test::Hardware::Accelerometer
{
    // Register test
    CPPUNIT_TEST_SUB_SUITE(
	    AccelerometerDummy,
	    Accelerometer
	);

    // Add the custom Dummy tests
    CPPUNIT_TEST(testSetAndGetDelta);
    
    CPPUNIT_TEST_SUITE_END();

private:

protected:

    /**
     * Instance of the accelerometer to test
     */
    dashee::Hardware::AccelerometerDummy * accelerometer;

    virtual void testConstructDefault();
    virtual void testUpdateAndRead();
    virtual void testSetAndGetDelta();

public:
    virtual void setUp();
    virtual void tearDown();
};

#endif

