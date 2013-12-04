/**
 * @file tests/Servo/Dummy.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_TEST_SERVO_DUMMY_H_
#define DASHEE_TEST_SERVO_DUMMY_H_

/**
 * Include Locals
 */
#include <dashee/Servo/Dummy.h>
#include "Servo.h"

/**
 * Set the name space
 */
namespace dashee
{
    namespace test
    {
        class ServoDummy;
    }
}

/**
 * Class which only creates an instance
 * ServoDummy and the base class sets and runs all the known
 * tests
 */
class dashee::test::ServoDummy : public dashee::test::Servo
{
    CPPUNIT_TEST_SUB_SUITE(
            dashee::test::ServoDummy,
            dashee::test::Servo
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
