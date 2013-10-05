/**
 * @file tests/ServoController.h
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

#ifndef DASHEE_TEST_SERVOCONTROLLER_H_
#define DASHEE_TEST_SERVOCONTROLLER_H_

#include <cppunit/extensions/HelperMacros.h>
#include <dashee/ServoController.h>

/**
 * Set the namespace
 */
namespace dashee
{
    namespace test
    {
        class ServoController;
    }
}

/**
 * ServoController test class for
 * unit testing known components
 */
class dashee::test::ServoController : public CppUnit::TestFixture
{
    // Register test
    CPPUNIT_TEST_SUITE(dashee::test::ServoController);
    
    // Set and Gets
    CPPUNIT_TEST(testSetAndGetTarget);
    CPPUNIT_TEST(testSetAndGetTargetDefault);
    CPPUNIT_TEST(testSetAndGetTargetFallback);
    CPPUNIT_TEST(testSetAndGetTargetFallbackEnabled);

    // Revert and Fallback
    CPPUNIT_TEST(testFallbackAndRevertTarget);
    
    // Exception
    CPPUNIT_TEST_EXCEPTION(testExceptionInvalidFile, dashee::ExceptionServoController);
    CPPUNIT_TEST_EXCEPTION(testExceptionInvalidChannel, dashee::ExceptionOutOfBounds);
    CPPUNIT_TEST_EXCEPTION(testExceptionInvalidPositiveTarget, dashee::ExceptionServo);
    CPPUNIT_TEST_EXCEPTION(testExceptionInvalidNegativeTarget, dashee::ExceptionServo);
    CPPUNIT_TEST_EXCEPTION(testExceptionInvalidLargePositiveTarget, dashee::ExceptionServo);
    CPPUNIT_TEST_EXCEPTION(testExceptionInvalidLargeNegativeTarget, dashee::ExceptionServo);

    // End
    CPPUNIT_TEST_SUITE_END();

private:

protected:

    // Handle to the pointer element which holds the ServoController
    dashee::ServoController * servoController;

    // test setTarget and getTarget
    void testSetAndGetTarget();

    // test setTargetDefault and getTargetDefault
    void testSetAndGetTargetDefault();

    // test setTargetFallback and getTargetFallback
    void testSetAndGetTargetFallback();

    // test setTargetFallbackEnabled and getTargetFallbackEnabled
    void testSetAndGetTargetFallbackEnabled();
    
    // test the revert and fallback functionality
    void testFallbackAndRevertTarget();
    
    // test exception when file is invalid
    virtual void testExceptionInvalidFile();

    // test exception when an unknown channel is requested
    void testExceptionInvalidChannel();

    // test exception when the target is greater than the range
    void testExceptionInvalidPositiveTarget();

    // test exception when the target is lower than the range
    void testExceptionInvalidNegativeTarget();

    // test exception when a large positive number is added
    void testExceptionInvalidLargePositiveTarget();

    // test exception when a large negative number is added
    void testExceptionInvalidLargeNegativeTarget();

public:

    // Let the derived class deal with setting up the variables
    virtual void setUp();

    // Delete the pointer of servoController variable
    virtual void tearDown();
};

#endif
