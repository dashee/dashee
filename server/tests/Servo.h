/**
 * @file tests/Servo.h
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

#ifndef DASHEE_TEST_SERVO_H_
#define DASHEE_TEST_SERVO_H_

#include <cppunit/extensions/HelperMacros.h>
#include <dashee/Servo.h>

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
