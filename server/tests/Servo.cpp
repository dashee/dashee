#include "Servo.h"

/**
 * @throws ExceptionServoController because this function is abstract
 */
void dashee::test::Servo::setUp()
{
    throw dashee::ExceptionServo("This function is abstract");
}

/**
 * @throws ExceptionServoController because this function is abstract
 */
void dashee::test::Servo::testSetAndGetTarget()
{
    if (this->servo == NULL)
	CPPUNIT_FAIL("Servo is not defined in testSetAndGetTarget");

    for (unsigned short int x = 0; x <= 255; x++)
    {
        this->servo->setTarget(x);
        CPPUNIT_ASSERT(this->servo->getTarget() == x);
    }
}

/**
 * Exception is thrown when the target is invalid
 */
void dashee::test::Servo::testExceptionInvalidPositiveTarget()
{
    this->servo->setTarget(1000);
}

/**
 * Exception is thrown when the target is invalid
 */
void dashee::test::Servo::testExceptionInvalidNegativeTarget()
{
    this->servo->setTarget(-1000);
}

/**
 * Exception is thrown when the target is invalid and set to a 
 * very very large number
 */
void dashee::test::Servo::testExceptionInvalidLargePositiveTarget()
{
    this->servo->setTarget(100084);
}

/**
 * Exception is thrown when the target is invalid and set to a 
 * very very large negative number
 */
void dashee::test::Servo::testExceptionInvalidLargeNegativeTarget()
{
    this->servo->setTarget(-234128989934832);
}

/**
 * Clean up
 */
void dashee::test::Servo::tearDown()
{
    delete this->servo;
}
