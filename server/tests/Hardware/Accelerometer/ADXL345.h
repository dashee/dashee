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
#include <dashee/I2C.h>

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

    // Test constructors
    CPPUNIT_TEST(testConstructI2C);

    // Accelerometer normal operation tests
    CPPUNIT_TEST(testSetAndGetRange);
    CPPUNIT_TEST(testSetAndGetScaleType);
    CPPUNIT_TEST(testSetAndGetBandwidth);
    
    CPPUNIT_TEST(testUpdateAndRead);
    CPPUNIT_TEST(testUpdateAndReadScaledRaw);
    CPPUNIT_TEST(testUpdateAndReadScaledG);
    CPPUNIT_TEST(testUpdateAndReadScaledMS2);
    CPPUNIT_TEST(testUpdateAndReadScaledRadians);
    CPPUNIT_TEST(testUpdateAndReadScaledDegrees);

    // Test exceptions
    CPPUNIT_TEST_EXCEPTION(
	    testInvalidI2C,
	    dashee::ExceptionNullPointer
	);
    // Test exceptions
    CPPUNIT_TEST_EXCEPTION(
	    testInvalidRange,
	    dashee::Hardware::ExceptionAccelerometerADXL345
	);

    CPPUNIT_TEST_EXCEPTION(
	    testInvalidBandwidth,
	    dashee::Hardware::ExceptionAccelerometerADXL345
	);
    CPPUNIT_TEST_SUITE_END();

private:

    static const size_t iterateTimes = 500;

protected:

    /**
     * Instance of the accelerometer to test
     */
    dashee::Hardware::AccelerometerADXL345 * accelerometer;

    virtual void testConstructDefault();
    virtual void testConstructI2C();

    virtual void testSetAndGetRange();
    virtual void testSetAndGetScaleType();
    virtual void testSetAndGetBandwidth();

    // Read values from the sensor
    virtual void testUpdateAndRead();
    virtual void testUpdateAndReadScaledRaw();
    virtual void testUpdateAndReadScaledG();
    virtual void testUpdateAndReadScaledMS2();
    virtual void testUpdateAndReadScaledRadians();
    virtual void testUpdateAndReadScaledDegrees();

    // Exceptions
    virtual void testInvalidI2C();
    virtual void testInvalidRange();
    virtual void testInvalidBandwidth();

public:
    virtual void setUp();
    virtual void tearDown();
};

#endif
