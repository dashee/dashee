/**
 * @file tests/Hardware/Servo/UART.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_TEST_HARDWARE_SERVO_UART_H_
#define DASHEE_TEST_HARDWARE_SERVO_UART_H_

/**
 * Include Locals
 */
#include <dashee/GPIO.h>
#include <dashee/Hardware/Servo/UART.h>
#include <termios.h>
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
	    class ServoUART;
	}
    }
}

/**
 * Class which only creates an instance
 * ServoDummy and the base class sets and runs all the known
 * tests
 */
class dashee::test::Hardware::ServoUART 
    : public dashee::test::Hardware::Servo
{
    CPPUNIT_TEST_SUB_SUITE(
            dashee::test::Hardware::ServoUART,
            dashee::test::Hardware::Servo
        );
    CPPUNIT_TEST_SUITE_END();

private:
protected:

    int fd;

public:

    // SetUp and TearDown
    virtual void setUp();
    virtual void tearDown();
};

#endif
