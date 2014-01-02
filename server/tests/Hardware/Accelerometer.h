/**
 * @file tests/Hardware/Accelerometer.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_TEST_HARDWARE_ACCELEROMETER_H_
#define DASHEE_TEST_HARDWARE_ACCELEROMETER_H_

#include <dashee/Exception.h>
#include <dashee/Hardware/Accelerometer.h>
#include <cppunit/extensions/HelperMacros.h>

/*
 * Set the namespace
 */
namespace dashee
{
    namespace test
    {
        namespace Hardware
        {
            class Accelerometer;
        }
    }
}

/**
 * Test the Accelerometer class
 */
class dashee::test::Hardware::Accelerometer : public CppUnit::TestFixture
{
    
    CPPUNIT_TEST_SUITE(Accelerometer);

    CPPUNIT_TEST(testConstructDefault);
    CPPUNIT_TEST(testReadAndUpdate);

    CPPUNIT_TEST_SUITE_END();

private:

protected:

    virtual void testConstructDefault();

    virtual void testReadAndUpdate();

public:
    virtual void setUp();
    virtual void tearDown();
};

#endif
