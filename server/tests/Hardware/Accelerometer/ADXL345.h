/**
 * @file tests/Hardware/Accelerometer/ADXL345.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_TEST_HARDWARE_ACCELEROMETER_ADXL345_H_
#define DASHEE_TEST_HARDWARE_ACCELEROMETER_ADXL345_H_

#include "Hardware/Accelerometer.h"
#include <dashee/Hardware/Accelerometer/ADXL345.h>

/*
 * Set the namespace
 */
namespace dashee
{
    namespace test
    {
        namespace Hardware
        {
            class AccelerometerADXL345;
        }
    }
}

/**
 * Test the Accelerometer ADXL345 class
 */
class dashee::test::Hardware::AccelerometerADXL345
    : public dashee::test::Hardware::Accelerometer
{
    // Register test
    CPPUNIT_TEST_SUB_SUITE(
	    AccelerometerADXL345,
	    Accelerometer
	);

    // Add the custom ADXL345 tests
    
    CPPUNIT_TEST_SUITE_END();

private:

protected:

    /**
     * Instance of the accelerometer to test
     */
    dashee::Hardware::AccelerometerADXL345 * accelerometer;

    virtual void testConstructDefault();
    //virtual void testConstructI2C();
    //virtual void testConstructCopy();
    //virtual void testConstructAssingment();

    virtual void testReadAndUpdate();

public:
    virtual void setUp();
    virtual void tearDown();
};

#endif
