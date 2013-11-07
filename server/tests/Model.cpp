#include "Model.h"

/**
 * Construct. 
 *
 * Set some constant values
 */ 
dashee::test::Model::Model()
{
}

/**
 * Start up, and check to ensure that our 
 * servocontrollers and server pointers are not null
 */ 
void dashee::test::Model::setUp()
{
    if (dashee::test::Model::servoController == NULL)
	throw dashee::ExceptionModel("ServoController must not be null");
    if (dashee::test::Model::server == NULL)
	throw dashee::ExceptionModel("Server must not be null");
}

/**
 * Run a sleep. 
 *
 * Because usleep(0) seems to be slow regardless, so we
 * overwrite this functio
 */
void dashee::test::Model::sleep()
{
    if (MODEL_TIMEOUT == 0)
        return;

    usleep(MODEL_TIMEOUT);
}

/**
 * Set up a similar server with a port +1.
 *
 * Do some dynamic casting to set the new Server Model,
 * Once created use set and get
 */
void dashee::test::Model::testSetAndGetServer()
{
    dashee::Server * oldServer = dashee::test::Model::server;
    dashee::Server * newServer = NULL;
    int port = oldServer->getPort()+1;
    
    if (dynamic_cast<ServerUDP *>(oldServer) != NULL)
	newServer = new dashee::ServerUDP(port);
    else
	throw dashee::Exception("dynamic cast failed.");

    this->model->setServer(newServer);
    CPPUNIT_ASSERT(newServer == this->model->getServer());

    this->model->setServer(oldServer);
    CPPUNIT_ASSERT(oldServer == this->model->getServer());

    delete newServer;
}

/**
 * We can't really test this accuratly as only one handle
 * can be open to a servocontroller.
 *
 * But we can test GET value
 */
void dashee::test::Model::testSetAndGetServoController()
{
    CPPUNIT_ASSERT(
            dashee::test::Model::servoController == 
            this->model->getServoController()
        );
}

/**
 * Test pitch value.
 * 
 * First test from 0-255, then test from 255-0, then from 0-255 in increments of
 * 8 and lastly 255-0 in increments of 8
 */
void dashee::test::Model::testSetAndGetPitch()
{
    CPPUNIT_ASSERT(this->model->getPitch() == 0);

    for (int x = 0; x < 256; x++)
    {
	this->model->setPitch(x);
	CPPUNIT_ASSERT(this->model->getPitch() == x);
        sleep();
    }
    
    for (int x = 255; x >= 0; x--)
    {
	this->model->setPitch(x);
	CPPUNIT_ASSERT(this->model->getPitch() == x);
        sleep();
    }
    
    for (int x = 0; x < 256; x=x+8)
    {
	this->model->setPitch(x);
	CPPUNIT_ASSERT(this->model->getPitch() == x);
        sleep();
    }
    
    for (int x = 255; x >= 0; x=x-8)
    {
	this->model->setPitch(x);
	CPPUNIT_ASSERT(this->model->getPitch() == x);
        sleep();
    }
    
    this->model->setPitch(128);
    CPPUNIT_ASSERT(this->model->getPitch() == 128);
    sleep();
}

/**
 * Test the roll value
 *
 * First test from 0-255, then test from 255-0, then from 0-255 in increments of
 * 8 and lastly 255-0 in increments of 8
 */
void dashee::test::Model::testSetAndGetRoll()
{
    CPPUNIT_ASSERT(this->model->getRoll() == 128);

    for (int x = 0; x < 256; x++)
    {
	this->model->setRoll(x);
	CPPUNIT_ASSERT(this->model->getRoll() == x);
        sleep();
    }
    
    for (int x = 255; x >= 0; x--)
    {
	this->model->setRoll(x);
	CPPUNIT_ASSERT(this->model->getRoll() == x);
        sleep();
    }
    
    for (int x = 0; x < 256; x=x+8)
    {
	this->model->setRoll(x);
	CPPUNIT_ASSERT(this->model->getRoll() == x);
        sleep();
    }
    
    for (int x = 255; x >= 0; x=x-8)
    {
	this->model->setRoll(x);
	CPPUNIT_ASSERT(this->model->getRoll() == x);
        sleep();
    }
    
    this->model->setRoll(128);
    CPPUNIT_ASSERT(this->model->getRoll() == 128);
    sleep();
}

/**
 * Test the yaw value
 * 
 * First test from 0-255, then test from 255-0, then from 0-255 in increments of
 * 8 and lastly 255-0 in increments of 8
 */
void dashee::test::Model::testSetAndGetYaw()
{
    CPPUNIT_ASSERT(this->model->getYaw() == 128);

    for (int x = 0; x < 256; x++)
    {
	this->model->setYaw(x);
	CPPUNIT_ASSERT(this->model->getYaw() == x);
        sleep();
    }

    for (int x = 255; x >= 0; x--)
    {
	this->model->setYaw(x);
	CPPUNIT_ASSERT(this->model->getYaw() == x);
        sleep();
    }

    for (int x = 0; x < 256; x=x+8)
    {
	this->model->setYaw(x);
	CPPUNIT_ASSERT(this->model->getYaw() == x);
        sleep();
    }
    
    for (int x = 255; x >= 0; x=x-8)
    {
	this->model->setYaw(x);
	CPPUNIT_ASSERT(this->model->getYaw() == x);
        sleep();
    }
    
    this->model->setYaw(128);
    CPPUNIT_ASSERT(this->model->getYaw() == 128);
    sleep();
}

/**
 * Test the Throttle value.
 */
void dashee::test::Model::testSetAndGetThrottle()
{
    CPPUNIT_ASSERT(this->model->getThrottle() == 0);

    for (int x = 0; x < 256; x++)
    {
	this->model->setThrottle(x);
	CPPUNIT_ASSERT(this->model->getThrottle() == x);
        sleep();
    }
    
    // Reset the throttle
    this->model->setThrottle(0);
    CPPUNIT_ASSERT(this->model->getThrottle() == 0);
    sleep();

    for (int x = 0; x < 256; x=x+8)
    {
	this->model->setYaw(x);
	CPPUNIT_ASSERT(this->model->getYaw() == x);
        sleep();
    }

    // Reset the throttle
    this->model->setThrottle(0);
    CPPUNIT_ASSERT(this->model->getThrottle() == 0);
    sleep();
}

/**
 * Test the pitch Trim
 *
 * For each trim value, test the 0-255 range and 255-0 range
 * of the pitch. Also for each trim and each range we check to see
 * the true/false parameter to setControl to ensure when asking for
 * a getControl value with notrim set to true the value is returned 
 * of the control surface without the trim compensation
 */
void dashee::test::Model::testSetAndGetPitchTrim()
{
    CPPUNIT_ASSERT(this->model->getPitchTrim() == 0);

    for (int x = -128; x < 128; x++)
    {
       this->model->setPitchTrim(x);

       for (int y = 0; y < 256; y++)
       {
            this->model->setPitch(y);
            CPPUNIT_ASSERT(
                    this->model->getPitch() == dashee::constrain(
                        (y - x),
                        0, 
                        255
                    ) 
                );
            CPPUNIT_ASSERT(this->model->getPitch(true) == y);
            sleep();
       }

       for (int y = 255; y >= 0; y--)
       {
            this->model->setPitch(y);
            CPPUNIT_ASSERT(
                    this->model->getPitch() == dashee::constrain(
                        (y - x),
                        0, 
                        255
                    ) 
                );
            CPPUNIT_ASSERT(this->model->getPitch(true) == y);
            sleep();
       }
    }

    this->model->setPitchTrim(0);
    this->model->setPitch(0);
    CPPUNIT_ASSERT(this->model->getPitchTrim() == 0);
    CPPUNIT_ASSERT(this->model->getPitch() == 0);
}

/**
 * Test roll trim.
 *
 * @see testSetAndGetPitchTrim for description
 */
void dashee::test::Model::testSetAndGetRollTrim()
{
    CPPUNIT_ASSERT(this->model->getRollTrim() == 0);

    for (int x = -128; x < 128; x++)
    {
       this->model->setRollTrim(x);

       for (int y = 0; y < 256; y++)
       {
            this->model->setRoll(y);
            CPPUNIT_ASSERT(
                    this->model->getRoll() == dashee::constrain(
                        (y - x),
                        0, 
                        255
                    ) 
                );
            CPPUNIT_ASSERT(this->model->getRoll(true) == y);
            sleep();
       }

       for (int y = 255; y >= 0; y--)
       {
            this->model->setRoll(y);
            CPPUNIT_ASSERT(
                    this->model->getRoll() == dashee::constrain(
                        (y - x),
                        0, 
                        255
                    ) 
                );
            CPPUNIT_ASSERT(this->model->getRoll(true) == y);
            sleep();
       }
    }

    this->model->setRollTrim(0);
    this->model->setRoll(0);
    CPPUNIT_ASSERT(this->model->getRollTrim() == 0);
    CPPUNIT_ASSERT(this->model->getRoll() == 0);
}

/**
 * Test yaw trim.
 *
 * @see testSetAndGetPitchTrim for description
 */
void dashee::test::Model::testSetAndGetYawTrim()
{
    CPPUNIT_ASSERT(this->model->getYawTrim() == 0);

    for (int x = -128; x < 128; x++)
    {
       this->model->setYawTrim(x);

       for (int y = 0; y < 256; y++)
       {
            this->model->setYaw(y);
            CPPUNIT_ASSERT(
                    this->model->getYaw() == dashee::constrain(
                        (y - x),
                        0, 
                        255
                    ) 
                );
            CPPUNIT_ASSERT(this->model->getYaw(true) == y);
            sleep();
       }

       for (int y = 255; y >= 0; y--)
       {
            this->model->setYaw(y);
            CPPUNIT_ASSERT(
                    this->model->getYaw() == dashee::constrain(
                        (y - x),
                        0, 
                        255
                    ) 
                );
            CPPUNIT_ASSERT(this->model->getYaw(true) == y);
            sleep();
       }
    }

    this->model->setYawTrim(0);
    this->model->setYaw(0);
    CPPUNIT_ASSERT(this->model->getYawTrim() == 0);
    CPPUNIT_ASSERT(this->model->getYaw() == 0);
}

/**
 * Test throttle trim.
 *
 * @see testSetAndGetPitchTrim for description
 */
void dashee::test::Model::testSetAndGetThrottleTrim()
{
    CPPUNIT_ASSERT(this->model->getThrottleTrim() == 0);

    for (int x = -128; x < 128; x++)
    {
       this->model->setThrottleTrim(x);

       for (int y = 0; y < 256; y++)
       {
            this->model->setThrottle(y);
            CPPUNIT_ASSERT(
                    this->model->getThrottle() == dashee::constrain(
                        (y - x),
                        0, 
                        255
                    ) 
                );
            CPPUNIT_ASSERT(this->model->getThrottle(true) == y);
            sleep();
       }

       for (int y = 255; y >= 0; y--)
       {
            this->model->setThrottle(y);
            CPPUNIT_ASSERT(
                    this->model->getThrottle() == dashee::constrain(
                        (y - x),
                        0, 
                        255
                    ) 
                );
            CPPUNIT_ASSERT(this->model->getThrottle(true) == y);
            sleep();
       }
    }

    this->model->setThrottleTrim(0);
    this->model->setThrottle(0);
    CPPUNIT_ASSERT(this->model->getThrottleTrim() == 0);
    CPPUNIT_ASSERT(this->model->getThrottle() == 0);
}

// Test fallback and revert modes
void dashee::test::Model::testFallbackAndRevert()
{
    // Test default values
    CPPUNIT_ASSERT(this->model->getPitchFallback() == 128);
    CPPUNIT_ASSERT(this->model->getRollFallback() == 128);
    CPPUNIT_ASSERT(this->model->getYawFallback() == 128);
    CPPUNIT_ASSERT(this->model->getThrottleFallback() == 128);

    CPPUNIT_ASSERT(this->model->isFallback() == false);
    this->model->revert();
    CPPUNIT_ASSERT(this->model->isFallback() == false);
    this->model->fallback();
    CPPUNIT_ASSERT(this->model->isFallback() == true);
    this->model->revert();
    CPPUNIT_ASSERT(this->model->isFallback() == false);

    for (int x = 0; x < 255; x++)
    {
        this->model->revert();
        CPPUNIT_ASSERT(this->model->isFallback() == false);
            
        this->model->setPitchFallback(x);
        CPPUNIT_ASSERT(this->model->getPitchFallback() == x);
        
        this->model->setRollFallback(x);
        CPPUNIT_ASSERT(this->model->getPitchFallback() == x);
        
        this->model->setYawFallback(x);
        CPPUNIT_ASSERT(this->model->getPitchFallback() == x);

        this->model->setThrottleFallback(x);
        CPPUNIT_ASSERT(this->model->getPitchFallback() == x);

        // TODO Test the pitch values after fallback
        this->model->fallback();
        CPPUNIT_ASSERT(this->model->getPitch() == x);
        CPPUNIT_ASSERT(this->model->getRoll() == x);
        CPPUNIT_ASSERT(this->model->getYaw() == x);
        CPPUNIT_ASSERT(this->model->getThrottle() == x);

        sleep();
    }
}

/**
 * Test the exceptions when setting NULL pointers
 */
void dashee::test::Model::testExceptionModelsetServerToNull()
{
    this->model->setServer(NULL);
}

/**
 * Test the exceptions when setting NULL pointers
 */
void dashee::test::Model::testExceptionModelsetServoControllerToNull()
{
    this->model->setServoController(NULL);
}

/**
 * Test Invalid value of Pitch
 */
void dashee::test::Model::testExceptionModelsetPitchNoRange()
{
    this->model->setPitch(-1000);
}

/**
 * Test Invalid value of Roll
 */
void dashee::test::Model::testExceptionModelsetRollNoRange()
{
    this->model->setRoll(-1000);
}

/**
 * Test Invalid value of Yaw
 */
void dashee::test::Model::testExceptionModelsetYawNoRange()
{
    this->model->setYaw(-1000);
}

/**
 * Test Invalid value of Throttle
 */
void dashee::test::Model::testExceptionModelsetThrottleNoRange()
{
    this->model->setThrottle(-1000);
}

/**
 * Test Invalid value of Pitch Trim
 */
void dashee::test::Model::testExceptionModelsetPitchTrimNoRange()
{
    this->model->setPitchTrim(-1000);
}

/**
 * Test Invalid value of Roll Trim
 */
void dashee::test::Model::testExceptionModelsetRollTrimNoRange()
{
    this->model->setRollTrim(-1000);
}

/**
 * Test Invalid value of Yaw Trim
 */
void dashee::test::Model::testExceptionModelsetYawTrimNoRange()
{
    this->model->setYawTrim(-1000);
}

/**
 * Test Invalid value of Throttle Trim
 */
void dashee::test::Model::testExceptionModelsetThrottleTrimNoRange()
{
    this->model->setThrottle(-1000);
}

/**
 * Clean up
 */
void dashee::test::Model::tearDown()
{
    delete model;
}

dashee::ServoController * dashee::test::Model::servoController = NULL;
dashee::Server * dashee::test::Model::server = NULL;
unsigned int dashee::test::Model::MODEL_TIMEOUT = 1;
