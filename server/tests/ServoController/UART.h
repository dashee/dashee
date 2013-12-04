/**
 * @file tests/ServoController/UART.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_TEST_SERVOCONTROLLER_UART_H_
#define DASHEE_TEST_SERVOCONTROLLER_UART_H_

/**
 * Include Locals
 */
#include <dashee/ServoController/UART.h>
#include "ServoController.h"

/**
 * Set the name space
 */
namespace dashee
{
    namespace test
    {
        class ServoControllerUART;
    }
}

/**
 * Class which only creates an instance
 * ServoControllerDummy and the base class sets and runs all the known
 * tests
 */
class dashee::test::ServoControllerUART : public dashee::test::ServoController
{
    CPPUNIT_TEST_SUB_SUITE(
            dashee::test::ServoControllerUART,
            dashee::test::ServoController
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
