/**
 * @file tests/Servo/UART.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_TEST_SERVO_UART_H_
#define DASHEE_TEST_SERVO_UART_H_

/**
 * Include Locals
 */
#include <dashee/Servo/UART.h>
#include "Servo.h"
#include <termios.h>

/**
 * Set the name space
 */
namespace dashee
{
    namespace test
    {
        class ServoUART;
    }
}

/**
 * Class which only creates an instance
 * ServoDummy and the base class sets and runs all the known
 * tests
 */
class dashee::test::ServoUART : public dashee::test::Servo
{
    CPPUNIT_TEST_SUB_SUITE(
            dashee::test::ServoUART,
            dashee::test::Servo
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
