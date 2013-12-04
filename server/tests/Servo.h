/**
 * @file tests/Servo.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_TEST_SERVO_H_
#define DASHEE_TEST_SERVO_H_

#include <cppunit/extensions/HelperMacros.h>
#include <dashee/Servo.h>
#include <dashee/Servo/UART.h>
#include "dashee.h"

/**
 * Set the namespace
 */
namespace dashee
{
    namespace test
    {
        class Servo;
    }
}

/**
 * Servo test class for
 * unit testing known components
 */
class dashee::test::Servo : public CppUnit::TestFixture
{
    // Register test
    CPPUNIT_TEST_SUITE(dashee::test::Servo);
    
    // Set and Gets
    CPPUNIT_TEST(testSetAndGetTarget);
    
    // Exception
    CPPUNIT_TEST_EXCEPTION(testExceptionInvalidPositiveTarget, dashee::ExceptionServo);
    CPPUNIT_TEST_EXCEPTION(testExceptionInvalidNegativeTarget, dashee::ExceptionServo);
    CPPUNIT_TEST_EXCEPTION(testExceptionInvalidLargePositiveTarget, dashee::ExceptionServo);
    CPPUNIT_TEST_EXCEPTION(testExceptionInvalidLargeNegativeTarget, dashee::ExceptionServo);

    // End
    CPPUNIT_TEST_SUITE_END();

private:

protected:

    // Handle to the servo
    dashee::Servo * servo;

    // test setTarget and getTarget
    virtual void testSetAndGetTarget();

    // Check invalid exception when target is set
    void testExceptionInvalidPositiveTarget();
    void testExceptionInvalidNegativeTarget();
    void testExceptionInvalidLargePositiveTarget();
    void testExceptionInvalidLargeNegativeTarget();

public:

    // Let the derived class deal with setting up the variables
    virtual void setUp();

    // Delete the pointer of servoController variable
    virtual void tearDown();

};

#endif
