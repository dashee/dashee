#include "Hardware/ServoController/UART.h"

using namespace dashee::test::Hardware;

/**
 * Create a new instance of ServoControllerDummy and 
 * set it to the private variable
 */
void ServoControllerUART::setUp()
{
    this->servoController 
	= new dashee::Hardware::ServoControllerUART("/dev/ttyAMA0", 12);
}

/**
 * Test the size command
 */
void ServoControllerUART::testSizeValue()
{
    CPPUNIT_ASSERT(this->servoController->size() == 12);
}

/**
 * Catch an exception when an invalid file is called
 */
void ServoControllerUART::testExceptionInvalidFile()
{
    this->servoController 
	= new dashee::Hardware::ServoControllerUART("poop", 6);
}

