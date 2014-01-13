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
 * @throws ExceptionServoController because this function is abstract
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
        CPPUNIT_ASSERT(this->servo->getTarget(true) == x);
        CPPUNIT_ASSERT(this->servo->getTarget(false) == x);

        dashee::sleep(timeout);
    }
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
    this->servo->setTarget(100084);
}

/**
 * Exception is thrown when the target is invalid and set to a 
 * very very large negative number
 */
void Servo::testExceptionInvalidLargeNegativeTarget()
{
    this->servo->setTarget(-234128989934832);
}

/**
 * Clean up
 */
void Servo::tearDown()
{
    delete this->servo;
}
