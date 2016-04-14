/**
 * @file tests/Hardware/ServoController/UART.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_TEST_HARDWARE_SERVOCONTROLLER_UART_H_
#define DASHEE_TEST_HARDWARE_SERVOCONTROLLER_UART_H_

/**
 * Include Locals
 */
#include <dashee/Hardware/ServoController/UART.h>
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
	    class ServoControllerUART;
	}
    }
}

/**
 * Class which only creates an instance
 * ServoControllerDummy and the base class sets and runs all the known
 * tests
 */
class dashee::test::Hardware::ServoControllerUART 
    : public dashee::test::Hardware::ServoController
{
    CPPUNIT_TEST_SUB_SUITE(
            dashee::test::Hardware::ServoControllerUART,
            dashee::test::Hardware::ServoController
        );

    CPPUNIT_TEST_SUITE_END();

private:
protected:
    
    // @Override
    virtual void testExceptionInvalidFile();
    virtual void testSizeValue();

public:

    // @Override
    virtual void setUp();
};

#endif
