#include "Vehicle.h"

using namespace dashee::test;

/**
 * Construct. 
 *
 * Set some constant values
 */ 
Vehicle::Vehicle()
{
}

/**
 * Start up, and check to ensure that our servocontrollers pointers should not 
 * be null
 */ 
void Vehicle::setUp()
{
    if (Vehicle::servoController == NULL)
	throw dashee::ExceptionVehicle("ServoController must not be null");
}

/**
 * We can't really test this accurately as only one handle
 * can be open to a servocontroller.
 *
 * But we can test GET value
 */
void Vehicle::testSetAndGetServoController()
{
    CPPUNIT_ASSERT(
            Vehicle::servoController == 
            this->vehicle->getServoController()
        );
}

/**
 * Test pitch value.
 * 
 * First test from 0-255, then test from 255-0, then from 0-255 in increments of
 * 8 and lastly 255-0 in increments of 8
 */
void Vehicle::testSetAndGetPitch()
{
    CPPUNIT_ASSERT(this->vehicle->getPitch() == 128);

    for (int x = 0; x < 256; x++)
    {
	this->vehicle->setPitch(x);
	CPPUNIT_ASSERT(this->vehicle->getPitch() == x);
    }
    
    this->vehicle->setPitch(128);
    CPPUNIT_ASSERT(this->vehicle->getPitch() == 128);
}

/**
 * Test the roll value
 *
 * First test from 0-255, then test from 255-0, then from 0-255 in increments of
 * 8 and lastly 255-0 in increments of 8
 */
void Vehicle::testSetAndGetRoll()
{
    CPPUNIT_ASSERT(this->vehicle->getRoll() == 128);

    for (int x = 0; x < 256; x++)
    {
	this->vehicle->setRoll(x);
	CPPUNIT_ASSERT(this->vehicle->getRoll() == x);
    }
    
    this->vehicle->setRoll(128);
    CPPUNIT_ASSERT(this->vehicle->getRoll() == 128);
}

/**
 * Test the yaw value
 * 
 * First test from 0-255, then test from 255-0, then from 0-255 in increments of
 * 8 and lastly 255-0 in increments of 8
 */
void Vehicle::testSetAndGetYaw()
{
    CPPUNIT_ASSERT(this->vehicle->getYaw() == 128);

    for (int x = 0; x < 256; x++)
    {
	this->vehicle->setYaw(x);
	CPPUNIT_ASSERT(this->vehicle->getYaw() == x);
    }

    this->vehicle->setYaw(128);
    CPPUNIT_ASSERT(this->vehicle->getYaw() == 128);
}

/**
 * Test the Throttle value.
 */
void Vehicle::testSetAndGetThrottle()
{
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 0);

    for (int x = 0; x < 256; x++)
    {
	this->vehicle->setThrottle(x);
	CPPUNIT_ASSERT(this->vehicle->getThrottle() == x);
    }
    
    // Reset the throttle
    this->vehicle->setThrottle(0);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 0);
}

/**
 * Test the pitch Trim
 *
 * For each trim we check the value when the trim is x, and the value
 * is 0, and also when trim is x and the value is 255.
 *
 */
void Vehicle::testSetAndGetPitchTrim()
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
void Vehicle::testSetAndGetRollTrim()
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
void Vehicle::testSetAndGetYawTrim()
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
void Vehicle::testSetAndGetThrottleTrim()
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
       }
    }

    this->vehicle->setThrottleTrim(0);
    this->vehicle->setThrottle(0);
    CPPUNIT_ASSERT(this->vehicle->getThrottleTrim() == 0);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 0);
}

/**
 * This function is designed to call transform and test the throttle values.
 *
 * It must be implemented in child classes
 */
void Vehicle::testReadFromBuffer()
{
    throw dashee::Exception("This must be implemented by a child function");
}

/**
 * After reading from the server the update function applies the changes to 
 * the physical model so it is important to test the actual changes
 */
void Vehicle::testUpdate()
{
    throw dashee::Exception("This must be implemented by a child function");
}

/**
 * Create a dummy configuration file, and let our vehicle set the state from the
 * read configuration
 */
void Vehicle::testSetAndGetFromConfig()
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
void Vehicle::testFallbackAndRevert()
{
    throw dashee::Exception("This must be implemented by a child function");
}

/**
 * Test the exceptions when setting NULL pointers
 */
void Vehicle::testExceptionVehiclesetServoControllerToNull()
{
    this->vehicle->setServoController(NULL);
}

/**
 * Test Invalid value of Pitch
 */
void Vehicle::testExceptionVehiclesetPitchNoRange()
{
    this->vehicle->setPitch(-1000);
}

/**
 * Test Invalid value of Roll
 */
void Vehicle::testExceptionVehiclesetRollNoRange()
{
    this->vehicle->setRoll(-1000);
}

/**
 * Test Invalid value of Yaw
 */
void Vehicle::testExceptionVehiclesetYawNoRange()
{
    this->vehicle->setYaw(-1000);
}

/**
 * Test Invalid value of Throttle
 */
void Vehicle::testExceptionVehiclesetThrottleNoRange()
{
    this->vehicle->setThrottle(-1000);
}

/**
 * Test Invalid value of Pitch Trim
 */
void Vehicle::testExceptionVehiclesetPitchTrimNoRange()
{
    this->vehicle->setPitchTrim(-1000);
}

/**
 * Test Invalid value of Roll Trim
 */
void Vehicle::testExceptionVehiclesetRollTrimNoRange()
{
    this->vehicle->setRollTrim(-1000);
}

/**
 * Test Invalid value of Yaw Trim
 */
void Vehicle::testExceptionVehiclesetYawTrimNoRange()
{
    this->vehicle->setYawTrim(-1000);
}

/**
 * Test Invalid value of Throttle Trim
 */
void Vehicle::testExceptionVehiclesetThrottleTrimNoRange()
{
    this->vehicle->setThrottle(-1000);
}

/**
 * Clean up
 */
void Vehicle::tearDown()
{
    delete vehicle;
}

dashee::Hardware::ServoController * Vehicle::servoController = NULL;
unsigned int Vehicle::VEHICLE_TIMEOUT = 1;
