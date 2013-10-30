/**
 * @file tests/Model.h
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

#ifndef DASHEE_TEST_MODEL_H_
#define DASHEE_TEST_MODEL_H_

#include <cppunit/extensions/HelperMacros.h>
#include <dashee/Model.h>
#include <dashee/ServoController.h>
#include <dashee/Server/UDP.h>

/**
 * Set the namespace
 */
namespace dashee
{
    namespace test
    {
        class Model;
    }
}

/**
 * ServoController test class for
 * unit testing known components
 */
class dashee::test::Model : public CppUnit::TestFixture
{
    // Register test
    CPPUNIT_TEST_SUITE(dashee::test::Model);
    
    // test set and get model variables
    CPPUNIT_TEST(testSetAndGetServer);
    CPPUNIT_TEST(testSetAndGetServoController);

    // test set and get flight controls
    CPPUNIT_TEST(testSetAndGetPitch);
    CPPUNIT_TEST(testSetAndGetRoll);
    CPPUNIT_TEST(testSetAndGetYaw);
    CPPUNIT_TEST(testSetAndGetThrottle);

    // test set and get trim controls
    CPPUNIT_TEST(testSetAndGetPitchTrim);
    CPPUNIT_TEST(testSetAndGetRollTrim);
    CPPUNIT_TEST(testSetAndGetYawTrim);
    CPPUNIT_TEST(testSetAndGetThrottleTrim);

    // Test the pitch and roll by it self
    CPPUNIT_TEST(testPitch);
    CPPUNIT_TEST(testRoll);
    CPPUNIT_TEST(testYaw);
    CPPUNIT_TEST(testThrottle);

    // Test controls with trim enabled
    CPPUNIT_TEST(testPitchWithTrim);
    CPPUNIT_TEST(testRollWithTrim);
    CPPUNIT_TEST(testYawWithTrim);
    CPPUNIT_TEST(testThrottleWithTrim);

    // Test fallback and revert modes
    CPPUNIT_TEST(testFallback);
    CPPUNIT_TEST(testRevert);
    
    // Test invalid NULL when trying to set the follwoing
    CPPUNIT_TEST_EXCEPTION(
	    testExceptionModelsetServerToNull, 
	    dashee::ExceptionModel
	);
    CPPUNIT_TEST_EXCEPTION(
	    testExceptionModelsetServoControllerToNull, 
	    dashee::ExceptionModel
	);
    
    // Test invalid range when trying to set controls
    CPPUNIT_TEST_EXCEPTION(
	    testExceptionModelsetPitchNoRange, 
	    dashee::ExceptionModel
	);
    CPPUNIT_TEST_EXCEPTION(
	    testExceptionModelsetRollNoRange,
	    dashee::ExceptionModel
	);
    CPPUNIT_TEST_EXCEPTION(
	    testExceptionModelsetYawNoRange, 
	    dashee::ExceptionModel
	);
    CPPUNIT_TEST_EXCEPTION(
	    testExceptionModelsetThrottleNoRange, 
	    dashee::ExceptionModel
	);

    // Test invalid range when trying to set controls trim
    CPPUNIT_TEST_EXCEPTION(
	    testExceptionModelsetPitchTrimNoRange,
	    dashee::ExceptionModel
	);
    CPPUNIT_TEST_EXCEPTION(
	    testExceptionModelsetRollTrimNoRange,
	    dashee::ExceptionModel
	);
    CPPUNIT_TEST_EXCEPTION(
	    testExceptionModelsetYawTrimNoRange,
	    dashee::ExceptionModel
	);
    CPPUNIT_TEST_EXCEPTION(
	    testExceptionModelsetThrottleTrimNoRange,
	    dashee::ExceptionModel
	);

    // End
    CPPUNIT_TEST_SUITE_END();

private:
protected:
    
    dashee::Model * model;

    // test set and get model variables
    void testSetAndGetServer();
    void testSetAndGetServoController();

    // test set and get flight controls
    virtual void testSetAndGetPitch();
    virtual void testSetAndGetRoll();
    virtual void testSetAndGetYaw();
    virtual void testSetAndGetThrottle();

    // test set and get trim controls
    virtual void testSetAndGetPitchTrim();
    virtual void testSetAndGetRollTrim();
    virtual void testSetAndGetYawTrim();
    virtual void testSetAndGetThrottleTrim();

    // Test the pitch and roll by it self
    virtual void testPitch();
    virtual void testRoll();
    virtual void testYaw();
    virtual void testThrottle();

    // Test controls with trim enabled
    virtual void testPitchWithTrim();
    virtual void testRollWithTrim();
    virtual void testYawWithTrim();
    virtual void testThrottleWithTrim();

    // Test fallback and revert modes
    virtual void testFallback();
    virtual void testRevert();

    // Test invalid set values
    void testExceptionModelsetServerToNull();
    void testExceptionModelsetServoControllerToNull();
    
    void testExceptionModelsetPitchNoRange();
    void testExceptionModelsetRollNoRange();
    void testExceptionModelsetYawNoRange();
    void testExceptionModelsetThrottleNoRange();

    void testExceptionModelsetPitchTrimNoRange();
    void testExceptionModelsetRollTrimNoRange();
    void testExceptionModelsetYawTrimNoRange();
    void testExceptionModelsetThrottleTrimNoRange();

public:
    static dashee::ServoController * servoController;
    static dashee::Server * server;

    // Let the derived class deal with setting up the variables
    virtual void setUp();

    // Delete the pointer of servoController variable
    virtual void tearDown();
};

#endif
