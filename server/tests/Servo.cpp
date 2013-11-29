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
        
    unsigned int timeout = 15;
    if (dynamic_cast<ServoUART *>(this->servo) == NULL)
        timeout = 0;

    for (unsigned short int x = 0; x < 256; x++)
    {
        this->servo->setTarget(x);
        CPPUNIT_ASSERT(this->servo->getTarget(true) == x);
        CPPUNIT_ASSERT(this->servo->getTarget(false) == x);

        dashee::sleep(timeout);
    }

    for (unsigned short int x = 255; x > 0; --x)
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
