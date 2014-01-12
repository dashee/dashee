/**
 * @file tests/Hardware/ServoController/Dummy.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_TEST_HARDWARE_SERVOCONTROLLER_DUMMY_H_
#define DASHEE_TEST_HARDWARE_SERVOCONTROLLER_DUMMY_H_

/**
 * Include Locals
 */
#include <dashee/Hardware/ServoController/Dummy.h>
#include "Hardware/ServoController.h"

/**
 * Set the name space
 */
namespace dashee
{
    namespace test
    {
	namespace Hardware
	{
	    class ServoControllerDummy;
	}
    }
}

/**
 * Class which only creates an instance
 * ServoControllerDummy and the base class sets and runs all the known
 * tests
 */
class dashee::test::Hardware::ServoControllerDummy 
    : public dashee::test::Hardware::ServoController
{
    CPPUNIT_TEST_SUB_SUITE(
            dashee::test::Hardware::ServoControllerDummy,
            dashee::test::Hardware::ServoController
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
