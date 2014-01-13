/**
 * @file tests/Hardware/ServoController.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_TEST_HARDWARE_SERVOCONTROLLER_H_
#define DASHEE_TEST_HARDWARE_SERVOCONTROLLER_H_

#include <cppunit/extensions/HelperMacros.h>
#include <dashee/Hardware/ServoController.h>
#include <dashee/Hardware/ServoController/UART.h>
#include "dashee.h"

/**
 * Set the namespace
 */
namespace dashee
{
    namespace test
    {
	namespace Hardware
	{
	    class ServoController;
	}
    }
}

/**
 * ServoController test class for
 * unit testing known components
 */
class dashee::test::Hardware::ServoController 
    : public CppUnit::TestFixture
{
    // Register test
    CPPUNIT_TEST_SUITE(dashee::test::Hardware::ServoController);
    
    // Set and Gets
    CPPUNIT_TEST(testSetAndGetTarget);
    CPPUNIT_TEST(testSizeValue);
    
    // Exception
    CPPUNIT_TEST_EXCEPTION(
	    testExceptionInvalidFile, 
	    dashee::Hardware::ExceptionServoController
	);
    CPPUNIT_TEST_EXCEPTION(
	    testExceptionInvalidChannel, 
	    dashee::ExceptionOutOfBounds
	);
    CPPUNIT_TEST_EXCEPTION(
	    testExceptionInvalidPositiveTarget, 
	    dashee::Hardware::ExceptionServo
	);
    CPPUNIT_TEST_EXCEPTION(
	    testExceptionInvalidNegativeTarget, 
	    dashee::Hardware::ExceptionServo
	);
    CPPUNIT_TEST_EXCEPTION(
	    testExceptionInvalidLargePositiveTarget, 
	    dashee::Hardware::ExceptionServo
	);
    CPPUNIT_TEST_EXCEPTION(
	    testExceptionInvalidLargeNegativeTarget, 
	    dashee::Hardware::ExceptionServo
	);

    // End
    CPPUNIT_TEST_SUITE_END();

private:

protected:

    // Handle to the pointer element which holds the ServoController
    dashee::Hardware::ServoController * servoController;

    // test setTarget and getTarget
    void testSetAndGetTarget();
    
    // test the size function
    virtual void testSizeValue();
    
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
