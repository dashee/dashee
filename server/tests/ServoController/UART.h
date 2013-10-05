/**
 * @file tests/ServoController/UART.h
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
    
    virtual void testExceptionInvalidFile();

public:

    // Change the setup
    virtual void setUp();
};

#endif
