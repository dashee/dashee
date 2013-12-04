/**
 * @file tests/ServoController/Dummy.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_TEST_SERVOCONTROLLER_DUMMY_H_
#define DASHEE_TEST_SERVOCONTROLLER_DUMMY_H_

/**
 * Include Locals
 */
#include <dashee/ServoController/Dummy.h>
#include "ServoController.h"

/**
 * Set the name space
 */
namespace dashee
{
    namespace test
    {
        class ServoControllerDummy;
    }
}

/**
 * Class which only creates an instance
 * ServoControllerDummy and the base class sets and runs all the known
 * tests
 */
class dashee::test::ServoControllerDummy : public dashee::test::ServoController
{
    CPPUNIT_TEST_SUB_SUITE(
            dashee::test::ServoControllerDummy,
            dashee::test::ServoController
        );

    CPPUNIT_TEST_SUITE_END();

private:
protected:
    
    virtual void testExceptionInvalidFile();
    
    virtual void testSizeValue();

public:

    // Change the setup
    virtual void setUp();
};

#endif
