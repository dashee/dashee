/**
 * @file tests/Servo/Dummy.h
 * @author Shahmir Javaid
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. In general
 * you are free to copy, distribute, display, and perform the work, 
 * you are also free to make derivative works, under the following conditions:
 *  - Attribution    — You must give dashee's author credit.
 *  - Non-Commercial - You may not use this dashee for commercial 
 *                     purposes without permission.
 *  - Share Alike    — If you alter, transform, or build upon this work, 
 *                     you may distribute the resulting work only under a licence 
 *                     identical to this one.
 *
 * The terms and conditions are updated at http://dashee.co.uk/license. View the
 * project site for more details
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
