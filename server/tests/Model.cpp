#include "Model.h"

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
    CPPUNIT_ASSERT(dashee::test::Model::servoController == this->model->getServoController());
}

/**
 * Test pitch value
 */
void dashee::test::Model::testSetAndGetPitch()
{
    CPPUNIT_ASSERT(this->model->getPitch() == 0);

    for (int x = 0; x < 256; x++)
    {
	this->model->setPitch(x);
	CPPUNIT_ASSERT(this->model->getPitch() == x);
    }
}

/**
 * Test the roll value
 */
void dashee::test::Model::testSetAndGetRoll()
{
    CPPUNIT_ASSERT(this->model->getRoll() == 128);

    for (int x = 0; x < 256; x++)
    {
	this->model->setRoll(x);
	CPPUNIT_ASSERT(this->model->getRoll() == x);
    }
}

/**
 * Test the yaw value
 */
void dashee::test::Model::testSetAndGetYaw()
{
    CPPUNIT_ASSERT(this->model->getYaw() == 128);

    for (int x = 0; x < 256; x++)
    {
	this->model->setYaw(x);
	CPPUNIT_ASSERT(this->model->getYaw() == x);
    }
}

/**
 * Test the Throttle value
 */
void dashee::test::Model::testSetAndGetThrottle()
{
    CPPUNIT_ASSERT(this->model->getThrottle() == 0);

    for (int x = 0; x < 256; x++)
    {
	this->model->setThrottle(x);
	CPPUNIT_ASSERT(this->model->getThrottle() == x);
    }
}

/**
 * Test the pitch Trim
 */
void dashee::test::Model::testSetAndGetPitchTrim()
{

}

void dashee::test::Model::testSetAndGetRollTrim(){}
void dashee::test::Model::testSetAndGetYawTrim(){}
void dashee::test::Model::testSetAndGetThrottleTrim(){}

// Test the pitch and roll by it self
void dashee::test::Model::testPitch(){}
void dashee::test::Model::testRoll(){}
void dashee::test::Model::testYaw(){}
void dashee::test::Model::testThrottle(){}

// Test controls with trim enabled
void dashee::test::Model::testPitchWithTrim(){}
void dashee::test::Model::testRollWithTrim(){}
void dashee::test::Model::testYawWithTrim(){}
void dashee::test::Model::testThrottleWithTrim(){}

// Test fallback and revert modes
void dashee::test::Model::testFallback(){}
void dashee::test::Model::testRevert(){}

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
