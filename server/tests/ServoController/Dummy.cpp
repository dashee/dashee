#include "ServoController/Dummy.h"

/**
 * Create a new instance of ServoControllerDummy and 
 * set it to the private variable
 */
void dashee::test::ServoControllerDummy::setUp()
{
    this->servoController 
	= new dashee::ServoControllerDummy("data/Servo.bin", 12);
}

/**
 * Test the size command
 */
void dashee::test::ServoControllerDummy::testSizeValue()
{
    CPPUNIT_ASSERT(this->servoController->size() == 12);
}

/**
 * Catch an exception when an invalid file is called
 */
void dashee::test::ServoControllerDummy::testExceptionInvalidFile()
{
    this->servoController = new dashee::ServoControllerDummy("poop", 12);
}
