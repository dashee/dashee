/**
 * @file tests/Vehicle.h
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
 *                     you may distribute the resulting work only under a 
 *                     licence identical to this one.
 *
 * The terms and conditions are updated at http://dashee.co.uk/license. View the
 * project site for more details
 */

#ifndef DASHEE_TEST_MODEL_H_
#define DASHEE_TEST_MODEL_H_

#include <cppunit/extensions/HelperMacros.h>
#include <dashee/Vehicle.h>
#include <dashee/ServoController.h>
#include <dashee/Server/UDP.h>

/**
 * Set the namespace
 */
namespace dashee
{
    namespace test
    {
        class Vehicle;
    }
}

/**
 * ServoController test class for
 * unit testing known components
 */
class dashee::test::Vehicle : public CppUnit::TestFixture
{
    // Register test
    CPPUNIT_TEST_SUITE(dashee::test::Vehicle);
    
    // test set and get model variables
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
    
    // Test the transform queue value
    CPPUNIT_TEST(testTransforQueue);

    // Test getting and setting from config
    CPPUNIT_TEST(testSetAndGetFromConfig);

    // Test fallback and revert modes
    CPPUNIT_TEST(testFallbackAndRevert);
    
    // Test invalid NULL when trying to set the follwoing
    CPPUNIT_TEST_EXCEPTION(
	    testExceptionVehiclesetServoControllerToNull, 
	    dashee::ExceptionVehicle
	);
    
    // Test invalid range when trying to set controls
    CPPUNIT_TEST_EXCEPTION(
	    testExceptionVehiclesetPitchNoRange, 
	    dashee::ExceptionVehicle
	);
    CPPUNIT_TEST_EXCEPTION(
	    testExceptionVehiclesetRollNoRange,
	    dashee::ExceptionVehicle
	);
    CPPUNIT_TEST_EXCEPTION(
	    testExceptionVehiclesetYawNoRange, 
	    dashee::ExceptionVehicle
	);
    CPPUNIT_TEST_EXCEPTION(
	    testExceptionVehiclesetThrottleNoRange, 
	    dashee::ExceptionVehicle
	);

    // Test invalid range when trying to set controls trim
    CPPUNIT_TEST_EXCEPTION(
	    testExceptionVehiclesetPitchTrimNoRange,
	    dashee::ExceptionVehicle
	);
    CPPUNIT_TEST_EXCEPTION(
	    testExceptionVehiclesetRollTrimNoRange,
	    dashee::ExceptionVehicle
	);
    CPPUNIT_TEST_EXCEPTION(
	    testExceptionVehiclesetYawTrimNoRange,
	    dashee::ExceptionVehicle
	);
    CPPUNIT_TEST_EXCEPTION(
	    testExceptionVehiclesetThrottleTrimNoRange,
	    dashee::ExceptionVehicle
	);

    // End
    CPPUNIT_TEST_SUITE_END();

private:
protected:
    
    dashee::Vehicle * vehicle;

    // test set and get model variables
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
    
    // test running the transform function
    virtual void testTransforQueue();
    
    // test set and get from Configuration variable
    virtual void testSetAndGetFromConfig();

    // Test fallback and revert modes
    virtual void testFallbackAndRevert();

    // Test invalid set values
    void testExceptionVehiclesetServoControllerToNull();
    
    void testExceptionVehiclesetPitchNoRange();
    void testExceptionVehiclesetRollNoRange();
    void testExceptionVehiclesetYawNoRange();
    void testExceptionVehiclesetThrottleNoRange();

    void testExceptionVehiclesetPitchTrimNoRange();
    void testExceptionVehiclesetRollTrimNoRange();
    void testExceptionVehiclesetYawTrimNoRange();
    void testExceptionVehiclesetThrottleTrimNoRange();

public:
    Vehicle();

    /**
     * Simple variable that controls how long to timeout
     * before every command
     */
    static unsigned int VEHICLE_TIMEOUT;

    static dashee::ServoController * servoController;

    // Let the derived class deal with setting up the variables
    virtual void setUp();

    // Delete the pointer of servoController variable
    virtual void tearDown();
};

#endif
