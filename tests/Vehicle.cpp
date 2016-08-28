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

    dashee::Vehicle * temp
            = new dashee::Vehicle(Vehicle::servoController);

    this->vehicle = temp;
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

    config->set("pitch-channel", 1);
    config->set("roll-channel", 2);
    config->set("yaw-channel", 3);
    config->set("throttle-channel", 4);

    this->vehicle->loadFromConfig(config);

    CPPUNIT_ASSERT(this->vehicle->getPitch() == 10);
    CPPUNIT_ASSERT(this->vehicle->getRoll() == 10);
    CPPUNIT_ASSERT(this->vehicle->getYaw() == 10);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 10);

    CPPUNIT_ASSERT(this->vehicle->getPitchChannel() == 1);
    CPPUNIT_ASSERT(this->vehicle->getRollChannel() == 2);
    CPPUNIT_ASSERT(this->vehicle->getYawChannel() == 3);
    CPPUNIT_ASSERT(this->vehicle->getThrottleChannel() == 4);
    
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
    // Test default values
    CPPUNIT_ASSERT(this->vehicle->getPitchFallback() == 128);
    CPPUNIT_ASSERT(this->vehicle->getRollFallback() == 128);
    CPPUNIT_ASSERT(this->vehicle->getYawFallback() == 128);
    CPPUNIT_ASSERT(this->vehicle->getThrottleFallback() == 0);

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
        CPPUNIT_ASSERT(this->vehicle->getRollFallback() == x);

        this->vehicle->setYawFallback(x);
        CPPUNIT_ASSERT(this->vehicle->getYawFallback() == x);

        this->vehicle->setThrottleFallback(x);
        CPPUNIT_ASSERT(this->vehicle->getThrottleFallback() == x);

        // TODO Test the pitch values after fall back
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
 * Call transform on a static queue
 */
void Vehicle::testReadFromBuffer()
{
    dashee::Buffer<unsigned char> q;

    // Push one command and see the status
    q.push(0);
    q.push(0);
    q.push(1);
    q.push(2);
    q.push(3);
    this->vehicle->read(&q);
    CPPUNIT_ASSERT(this->vehicle->getPitch() == 0);
    CPPUNIT_ASSERT(this->vehicle->getRoll() == 1);
    CPPUNIT_ASSERT(this->vehicle->getYaw() == 2);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 3);
    CPPUNIT_ASSERT(q.empty() == true);

    // Push another command and see the changed
    q.push(0);
    q.push(10);
    q.push(11);
    q.push(12);
    q.push(13);
    this->vehicle->read(&q);
    CPPUNIT_ASSERT(this->vehicle->getPitch() == 10);
    CPPUNIT_ASSERT(this->vehicle->getRoll() == 11);
    CPPUNIT_ASSERT(this->vehicle->getYaw() == 12);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 13);
    CPPUNIT_ASSERT(q.empty() == true);

    // Push two commands and check that the values are set to the
    // last known value
    q.push(0);
    q.push(20);
    q.push(21);
    q.push(22);
    q.push(23);
    q.push(0);
    q.push(30);
    q.push(31);
    q.push(32);
    q.push(33);
    this->vehicle->read(&q);
    CPPUNIT_ASSERT(this->vehicle->getPitch() == 30);
    CPPUNIT_ASSERT(this->vehicle->getRoll() == 31);
    CPPUNIT_ASSERT(this->vehicle->getYaw() == 32);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 33);
    CPPUNIT_ASSERT(q.empty() == true);

    // Test invalid set of commands
    q.push(10);
    q.push(11);
    q.push(12);
    q.push(11);
    q.push(12);
    this->vehicle->read(&q);
    CPPUNIT_ASSERT(this->vehicle->getPitch() == 30);
    CPPUNIT_ASSERT(this->vehicle->getRoll() == 31);
    CPPUNIT_ASSERT(this->vehicle->getYaw() == 32);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 33);
    CPPUNIT_ASSERT(q.empty() == true);

    // Test invalid set of commands
    q.push(10);
    q.push(11);
    q.push(12);
    q.push(0);
    q.push(40);
    q.push(41);
    q.push(42);
    q.push(43);
    q.push(10);
    this->vehicle->read(&q);
    CPPUNIT_ASSERT(this->vehicle->getPitch() == 40);
    CPPUNIT_ASSERT(this->vehicle->getRoll() == 41);
    CPPUNIT_ASSERT(this->vehicle->getYaw() == 42);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 43);
    CPPUNIT_ASSERT(q.empty() == true);

    CPPUNIT_ASSERT(this->vehicle->getPitch() != 255);
    CPPUNIT_ASSERT(this->vehicle->getRoll() != 255);
    CPPUNIT_ASSERT(this->vehicle->getYaw() != 255);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() != 255);
}

/**
 * Test the changes from the motor it self
 */
void Vehicle::testUpdate()
{
    dashee::Hardware::ServoController * servoController
            = this->vehicle->getServoController();

    dashee::Vehicle * vehicle
            = static_cast<dashee::Vehicle *>(this->vehicle);

    vehicle->setYaw(10);
    vehicle->setPitch(11);
    vehicle->setRoll(12);
    vehicle->setThrottle(13);
    vehicle->update();

    CPPUNIT_ASSERT(
            servoController->getTarget(vehicle->getYawChannel()) == 10
    );
    CPPUNIT_ASSERT(
            servoController->getTarget(vehicle->getPitchChannel()) == 11
    );
    CPPUNIT_ASSERT(
            servoController->getTarget(vehicle->getRollChannel()) == 12
    );
    CPPUNIT_ASSERT(
            servoController->getTarget(vehicle->getThrottleChannel()) == 13
    );
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
