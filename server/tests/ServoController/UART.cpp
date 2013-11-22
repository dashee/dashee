#include "ServoController/UART.h"

/**
 * Create a new instance of ServoControllerDummy and 
 * set it to the private variable
 */
void dashee::test::ServoControllerUART::setUp()
{
    this->servoController = new dashee::ServoControllerUART("/dev/ttyAMA0", 12);
}

/**
 * Test the size command
 */
void dashee::test::ServoControllerUART::testSizeValue()
{
    CPPUNIT_ASSERT(this->servoController->size() == 12);
}

/**
 * Catch an exception when an invalid file is called
 */
void dashee::test::ServoControllerUART::testExceptionInvalidFile()
{
    this->servoController = new dashee::ServoControllerUART("poop", 6);
}

