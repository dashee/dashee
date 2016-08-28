#include "Hardware/Servo.h"

using namespace dashee::test::Hardware;

/**
 * @throws ExceptionServoController because this function is abstract
 */
void Servo::setUp()
{
    throw dashee::Hardware::ExceptionServo("This function is abstract");
}

/**
 * Test setting and getting the servo values
 */
void Servo::testSetAndGetTarget()
{
    if (this->servo == NULL)
	CPPUNIT_FAIL("Servo is not defined in testSetAndGetTarget");
        
    unsigned int timeout = 15;
    if (dynamic_cast<dashee::Hardware::ServoUART *>(this->servo) == NULL)
        timeout = 0;

    for (unsigned short int x = 0; x < 256; x++)
    {
        this->servo->setTarget(x);
        CPPUNIT_ASSERT(this->servo->getTarget() == x);
        CPPUNIT_ASSERT(this->servo->getTarget(true) == x);

        dashee::sleep(timeout);
    }
}

/**
 * Test the set and get of the Servo Target value when changing inverted
 */ 
void Servo::testSetAndGetTargetInverted()
{
    if (this->servo == NULL)
	CPPUNIT_FAIL("Servo is not defined in testSetAndGetTarget");
        
    unsigned int timeout = 15;
    if (dynamic_cast<dashee::Hardware::ServoUART *>(this->servo) == NULL)
        timeout = 0;

    CPPUNIT_ASSERT(this->servo->isInverted() == false);

    this->servo->invert(true);
    CPPUNIT_ASSERT(this->servo->isInverted());
    this->servo->setTarget(0);
    CPPUNIT_ASSERT(this->servo->getTarget() == 0);
    CPPUNIT_ASSERT(this->servo->getTarget(true) == 0);
    dashee::sleep(timeout);

    this->servo->invert(false);
    CPPUNIT_ASSERT(this->servo->isInverted() == false);
    CPPUNIT_ASSERT(this->servo->getTarget() == 255);
    CPPUNIT_ASSERT(this->servo->getTarget(true) == 255);
    dashee::sleep(timeout);
}

/**
 * Exception is thrown when the target is invalid
 */
void Servo::testExceptionInvalidPositiveTarget()
{
    this->servo->setTarget(1000);
}

/**
 * Exception is thrown when the target is invalid
 */
void Servo::testExceptionInvalidNegativeTarget()
{
    this->servo->setTarget(-1000);
}

/**
 * Exception is thrown when the target is invalid and set to a 
 * very very large number
 */
void Servo::testExceptionInvalidLargePositiveTarget()
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverflow"
    this->servo->setTarget(100084);
#pragma GCC diagnostic pop
}

/**
 * Exception is thrown when the target is invalid and set to a 
 * very very large negative number
 */
void Servo::testExceptionInvalidLargeNegativeTarget()
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverflow"
    this->servo->setTarget(-234128989934832);
#pragma GCC diagnostic pop
}

/**
 * Clean up
 */
void Servo::tearDown()
{
    delete this->servo;
}
