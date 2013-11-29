#include "Vehicle.h"

/**
 * Construct. 
 *
 * Set some constant values
 */ 
dashee::test::Vehicle::Vehicle()
{
}

/**
 * Start up, and check to ensure that our servocontrollers pointers should not 
 * be null
 */ 
void dashee::test::Vehicle::setUp()
{
    if (dashee::test::Vehicle::servoController == NULL)
	throw dashee::ExceptionVehicle("ServoController must not be null");
}

/**
 * We can't really test this accuratly as only one handle
 * can be open to a servocontroller.
 *
 * But we can test GET value
 */
void dashee::test::Vehicle::testSetAndGetServoController()
{
    CPPUNIT_ASSERT(
            dashee::test::Vehicle::servoController == 
            this->vehicle->getServoController()
        );
}

/**
 * Test pitch value.
 * 
 * First test from 0-255, then test from 255-0, then from 0-255 in increments of
 * 8 and lastly 255-0 in increments of 8
 */
void dashee::test::Vehicle::testSetAndGetPitch()
{
    CPPUNIT_ASSERT(this->vehicle->getPitch() == 0);

    for (int x = 0; x < 256; x++)
    {
	this->vehicle->setPitch(x);
	CPPUNIT_ASSERT(this->vehicle->getPitch() == x);
	dashee::sleep(VEHICLE_TIMEOUT);
    }
    
    for (int x = 255; x >= 0; x--)
    {
	this->vehicle->setPitch(x);
	CPPUNIT_ASSERT(this->vehicle->getPitch() == x);
	dashee::sleep(VEHICLE_TIMEOUT);
    }
    
    this->vehicle->setPitch(128);
    CPPUNIT_ASSERT(this->vehicle->getPitch() == 128);
    dashee::sleep(VEHICLE_TIMEOUT);
}

/**
 * Test the roll value
 *
 * First test from 0-255, then test from 255-0, then from 0-255 in increments of
 * 8 and lastly 255-0 in increments of 8
 */
void dashee::test::Vehicle::testSetAndGetRoll()
{
    CPPUNIT_ASSERT(this->vehicle->getRoll() == 128);

    for (int x = 0; x < 256; x++)
    {
	this->vehicle->setRoll(x);
	CPPUNIT_ASSERT(this->vehicle->getRoll() == x);
	dashee::sleep(VEHICLE_TIMEOUT);
    }
    
    for (int x = 255; x >= 0; x--)
    {
	this->vehicle->setRoll(x);
	CPPUNIT_ASSERT(this->vehicle->getRoll() == x);
	dashee::sleep(VEHICLE_TIMEOUT);
    }
    
    this->vehicle->setRoll(128);
    CPPUNIT_ASSERT(this->vehicle->getRoll() == 128);
    dashee::sleep(VEHICLE_TIMEOUT);
}

/**
 * Test the yaw value
 * 
 * First test from 0-255, then test from 255-0, then from 0-255 in increments of
 * 8 and lastly 255-0 in increments of 8
 */
void dashee::test::Vehicle::testSetAndGetYaw()
{
    CPPUNIT_ASSERT(this->vehicle->getYaw() == 128);

    for (int x = 0; x < 256; x++)
    {
	this->vehicle->setYaw(x);
	CPPUNIT_ASSERT(this->vehicle->getYaw() == x);
	dashee::sleep(VEHICLE_TIMEOUT);
    }

    for (int x = 255; x >= 0; x--)
    {
	this->vehicle->setYaw(x);
	CPPUNIT_ASSERT(this->vehicle->getYaw() == x);
	dashee::sleep(VEHICLE_TIMEOUT);
    }

    this->vehicle->setYaw(128);
    CPPUNIT_ASSERT(this->vehicle->getYaw() == 128);
    dashee::sleep(VEHICLE_TIMEOUT);
}

/**
 * Test the Throttle value.
 */
void dashee::test::Vehicle::testSetAndGetThrottle()
{
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 0);

    for (int x = 0; x < 256; x++)
    {
	this->vehicle->setThrottle(x);
	CPPUNIT_ASSERT(this->vehicle->getThrottle() == x);
	dashee::sleep(VEHICLE_TIMEOUT);
    }
    
    // Reset the throttle
    this->vehicle->setThrottle(0);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 0);
    dashee::sleep(VEHICLE_TIMEOUT);

    // Reset the throttle
    this->vehicle->setThrottle(0);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 0);
    dashee::sleep(VEHICLE_TIMEOUT);
}

/**
 * Test the pitch Trim
 *
 * For each trim we check the value when the trim is x, and the value
 * is 0, and also when trim is x and the value is 255.
 *
 */
void dashee::test::Vehicle::testSetAndGetPitchTrim()
{
    CPPUNIT_ASSERT(this->vehicle->getPitchTrim() == 0);

    for (int x = -128; x < 128; x++)
    {
	this->vehicle->setPitchTrim(x);

	for (int y = 0; y < 256; y++)
	{
	    this->vehicle->setPitch(y);
	    CPPUNIT_ASSERT(
	    this->vehicle->getPitch() == dashee::constrain(
			(y - x),
			0, 
			255
		    ) 
		);
	    CPPUNIT_ASSERT(this->vehicle->getPitch(true) == y);
	    dashee::sleep(VEHICLE_TIMEOUT);
	}
    }

    this->vehicle->setPitchTrim(0);
    this->vehicle->setPitch(0);
    CPPUNIT_ASSERT(this->vehicle->getPitchTrim() == 0);
    CPPUNIT_ASSERT(this->vehicle->getPitch() == 0);
}

/**
 * Test roll trim.
 *
 * @see testSetAndGetPitchTrim for description
 */
void dashee::test::Vehicle::testSetAndGetRollTrim()
{
    CPPUNIT_ASSERT(this->vehicle->getRollTrim() == 0);

    for (int x = -128; x < 128; x++)
    {
       this->vehicle->setRollTrim(x);

       for (int y = 0; y < 256; y++)
       {
            this->vehicle->setRoll(y);
            CPPUNIT_ASSERT(
                    this->vehicle->getRoll() == dashee::constrain(
                        (y - x),
                        0, 
                        255
                    ) 
                );
            CPPUNIT_ASSERT(this->vehicle->getRoll(true) == y);
            dashee::sleep(VEHICLE_TIMEOUT);
       }
    }

    this->vehicle->setRollTrim(0);
    this->vehicle->setRoll(0);
    CPPUNIT_ASSERT(this->vehicle->getRollTrim() == 0);
    CPPUNIT_ASSERT(this->vehicle->getRoll() == 0);
}

/**
 * Test yaw trim.
 *
 * @see testSetAndGetPitchTrim for description
 */
void dashee::test::Vehicle::testSetAndGetYawTrim()
{
    CPPUNIT_ASSERT(this->vehicle->getYawTrim() == 0);

    for (int x = -128; x < 128; x++)
    {
       this->vehicle->setYawTrim(x);

       for (int y = 0; y < 256; y++)
       {
            this->vehicle->setYaw(y);
            CPPUNIT_ASSERT(
                    this->vehicle->getYaw() == dashee::constrain(
                        (y - x),
                        0, 
                        255
                    ) 
                );
            CPPUNIT_ASSERT(this->vehicle->getYaw(true) == y);
            dashee::sleep(VEHICLE_TIMEOUT);
       }
    }

    this->vehicle->setYawTrim(0);
    this->vehicle->setYaw(0);
    CPPUNIT_ASSERT(this->vehicle->getYawTrim() == 0);
    CPPUNIT_ASSERT(this->vehicle->getYaw() == 0);
}

/**
 * Test throttle trim.
 *
 * @see testSetAndGetPitchTrim for description
 */
void dashee::test::Vehicle::testSetAndGetThrottleTrim()
{
    CPPUNIT_ASSERT(this->vehicle->getThrottleTrim() == 0);

    for (int x = -128; x < 128; x++)
    {
       this->vehicle->setThrottleTrim(x);

       for (int y = 0; y < 256; y++)
       {
            this->vehicle->setThrottle(y);
            CPPUNIT_ASSERT(
                    this->vehicle->getThrottle() == dashee::constrain(
                        (y - x),
                        0, 
                        255
                    ) 
                );
            CPPUNIT_ASSERT(this->vehicle->getThrottle(true) == y);
            dashee::sleep(VEHICLE_TIMEOUT);
       }
    }

    this->vehicle->setThrottleTrim(0);
    this->vehicle->setThrottle(0);
    CPPUNIT_ASSERT(this->vehicle->getThrottleTrim() == 0);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 0);
}

/**
 * Create a dummy configuration file, and let our vehicle set the state from the
 * read configuration
 */
void dashee::test::Vehicle::testSetAndGetFromConfig()
{
    dashee::Config * config = new Config();
    config->set("pitch", 10);
    config->set("roll", 10);
    config->set("yaw", 10);
    config->set("throttle", 10);
    
    config->set("pitch-fallback", 20);
    config->set("roll-fallback", 20);
    config->set("yaw-fallback", 20);
    config->set("throttle-fallback", 20);

    this->vehicle->loadFromConfig(config);

    CPPUNIT_ASSERT(this->vehicle->getPitch() == 10);
    CPPUNIT_ASSERT(this->vehicle->getRoll() == 10);
    CPPUNIT_ASSERT(this->vehicle->getYaw() == 10);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 10);
    
    CPPUNIT_ASSERT(this->vehicle->getPitchFallback() == 20);
    CPPUNIT_ASSERT(this->vehicle->getRollFallback() == 20);
    CPPUNIT_ASSERT(this->vehicle->getYawFallback() == 20);
    CPPUNIT_ASSERT(this->vehicle->getThrottleFallback() == 20);

    delete config;
}

/**
 * Test falling back and reverting
 */
void dashee::test::Vehicle::testFallbackAndRevert()
{
    // Test default values
    CPPUNIT_ASSERT(this->vehicle->getPitchFallback() == 128);
    CPPUNIT_ASSERT(this->vehicle->getRollFallback() == 128);
    CPPUNIT_ASSERT(this->vehicle->getYawFallback() == 128);
    CPPUNIT_ASSERT(this->vehicle->getThrottleFallback() == 128);

    CPPUNIT_ASSERT(this->vehicle->isFallback() == false);
    this->vehicle->revert();
    CPPUNIT_ASSERT(this->vehicle->isFallback() == false);
    this->vehicle->fallback();
    CPPUNIT_ASSERT(this->vehicle->isFallback() == true);
    this->vehicle->revert();
    CPPUNIT_ASSERT(this->vehicle->isFallback() == false);

    for (int x = 0; x < 255; x++)
    {
        this->vehicle->revert();
        CPPUNIT_ASSERT(this->vehicle->isFallback() == false);
            
        this->vehicle->setPitchFallback(x);
        CPPUNIT_ASSERT(this->vehicle->getPitchFallback() == x);
        
        this->vehicle->setRollFallback(x);
        CPPUNIT_ASSERT(this->vehicle->getPitchFallback() == x);
        
        this->vehicle->setYawFallback(x);
        CPPUNIT_ASSERT(this->vehicle->getPitchFallback() == x);

        this->vehicle->setThrottleFallback(x);
        CPPUNIT_ASSERT(this->vehicle->getPitchFallback() == x);

        // TODO Test the pitch values after fallback
        this->vehicle->fallback();
        CPPUNIT_ASSERT(this->vehicle->getPitch() == x);
        CPPUNIT_ASSERT(this->vehicle->getRoll() == x);
        CPPUNIT_ASSERT(this->vehicle->getYaw() == x);
        CPPUNIT_ASSERT(this->vehicle->getThrottle() == x);

        dashee::sleep(VEHICLE_TIMEOUT);
    }
}

/**
 * Test the exceptions when setting NULL pointers
 */
void dashee::test::Vehicle::testExceptionVehiclesetServoControllerToNull()
{
    this->vehicle->setServoController(NULL);
}

/**
 * Test Invalid value of Pitch
 */
void dashee::test::Vehicle::testExceptionVehiclesetPitchNoRange()
{
    this->vehicle->setPitch(-1000);
}

/**
 * Test Invalid value of Roll
 */
void dashee::test::Vehicle::testExceptionVehiclesetRollNoRange()
{
    this->vehicle->setRoll(-1000);
}

/**
 * Test Invalid value of Yaw
 */
void dashee::test::Vehicle::testExceptionVehiclesetYawNoRange()
{
    this->vehicle->setYaw(-1000);
}

/**
 * Test Invalid value of Throttle
 */
void dashee::test::Vehicle::testExceptionVehiclesetThrottleNoRange()
{
    this->vehicle->setThrottle(-1000);
}

/**
 * Test Invalid value of Pitch Trim
 */
void dashee::test::Vehicle::testExceptionVehiclesetPitchTrimNoRange()
{
    this->vehicle->setPitchTrim(-1000);
}

/**
 * Test Invalid value of Roll Trim
 */
void dashee::test::Vehicle::testExceptionVehiclesetRollTrimNoRange()
{
    this->vehicle->setRollTrim(-1000);
}

/**
 * Test Invalid value of Yaw Trim
 */
void dashee::test::Vehicle::testExceptionVehiclesetYawTrimNoRange()
{
    this->vehicle->setYawTrim(-1000);
}

/**
 * Test Invalid value of Throttle Trim
 */
void dashee::test::Vehicle::testExceptionVehiclesetThrottleTrimNoRange()
{
    this->vehicle->setThrottle(-1000);
}

/**
 * Clean up
 */
void dashee::test::Vehicle::tearDown()
{
    delete vehicle;
}

dashee::ServoController * dashee::test::Vehicle::servoController = NULL;
unsigned int dashee::test::Vehicle::VEHICLE_TIMEOUT = 1;
