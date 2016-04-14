#include "Hardware/ServoController/Dummy.h"

using namespace dashee::test::Hardware;

/**
 * Create a new instance of ServoControllerDummy and 
 * set it to the private variable
 */
void ServoControllerDummy::setUp()
{
    this->servoController 
	= new dashee::Hardware::ServoControllerDummy("data/Servo.bin", 12);
}

/**
 * Test the size command
 */
void ServoControllerDummy::testSizeValue()
{
    CPPUNIT_ASSERT(this->servoController->size() == 12);
}

/**
 * Catch an exception when an invalid file is called
 */
void ServoControllerDummy::testExceptionInvalidFile()
{
    this->servoController 
	= new dashee::Hardware::ServoControllerDummy("poop", 12);
}
