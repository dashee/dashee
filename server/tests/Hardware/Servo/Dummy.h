/**
 * @file tests/Hardware/Servo/Dummy.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_TEST_HARDWARE_SERVO_DUMMY_H_
#define DASHEE_TEST_HARDWARE_SERVO_DUMMY_H_

/**
 * Include Locals
 */
#include <dashee/Hardware/Servo/Dummy.h>
#include "Hardware/Servo.h"

/**
 * Set the name space
 */
namespace dashee
{
    namespace test
    {
	namespace Hardware
	{
	    class ServoDummy;
	}
    }
}

/**
 * Class which only creates an instance
 * ServoDummy and the base class sets and runs all the known
 * tests
 */
class dashee::test::Hardware::ServoDummy 
    : public dashee::test::Hardware::Servo
{
    CPPUNIT_TEST_SUB_SUITE(
            dashee::test::Hardware::ServoDummy,
            dashee::test::Hardware::Servo
        );
    CPPUNIT_TEST_SUITE_END();

private:
protected:

    FILE * fd;

public:

    // SetUp and TearDown
    virtual void setUp();
    virtual void tearDown();
};

#endif
