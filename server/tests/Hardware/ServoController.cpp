#include "Hardware/ServoController.h"

using namespace dashee::test::Hardware;

/**
 * Throw an exception because we cant have abstract classes
 * in CPPUnit this is a dumb way of doing it but it works
 *
 * @throws ExceptionServoController
 */
void ServoController::setUp()
{
    throw dashee::Hardware::ExceptionServoController("This class is abstract");
}

/**
 * This test will set the Servo Value, and see if the 
 * get value is correct
 *
 * @assert the values of the set servo's are the same
 */
void ServoController::testSetAndGetTarget()
{   
    unsigned int timeout = 15;
    if (dynamic_cast<dashee::Hardware::ServoControllerUART *>
	    (this->servoController) == NULL)
        timeout = 0;

    for (
            unsigned short int servos = 0; 
            servos < this->servoController->size(); 
            servos++
        ) 
    {
        for (unsigned short int x = 0; x <= 255; x++)
        {
            this->servoController->setTarget(servos, x);
            CPPUNIT_ASSERT(this->servoController->getTarget(servos) == x);
	    dashee::sleep(timeout);
        }
    }
}

/**
 * Test the values are correct when inverted
 */
void ServoController::testSetAndGetTargetInverted()
{
    unsigned int timeout = 15;
    if (dynamic_cast<dashee::Hardware::ServoControllerUART *>
	    (this->servoController) == NULL)
        timeout = 0;

    for (
            unsigned short int servos = 0; 
            servos < this->servoController->size(); 
            servos++
        ) 
    {
        CPPUNIT_ASSERT(this->servoController->isInverted(servos) == false);

        this->servoController->invert(servos, true);
        CPPUNIT_ASSERT(this->servoController->isInverted(servos));
        this->servoController->setTarget(servos, 0);
        CPPUNIT_ASSERT(this->servoController->getTarget(servos) == 0);
        dashee::sleep(timeout);

        this->servoController->invert(servos, false);
        CPPUNIT_ASSERT(this->servoController->isInverted(servos) == false);
        CPPUNIT_ASSERT(this->servoController->getTarget(servos) == 255);
        dashee::sleep(timeout);
    }
}

/**
 * Check the [] operator functions
 */
void ServoController::testOperatorSquareBracket()
{
    for (
            unsigned short int servos = 0; 
            servos < this->servoController->size(); 
            servos++
        ) 
    {
        dashee::Hardware::ServoController & sc = *this->servoController;

        CPPUNIT_ASSERT(
                &sc.getServo(servos) == &sc[servos]
            );
    }

}

/**
 * Checks the size of the servo value.
 *
 * @throws ExceptionServoController
 */ 
void ServoController::testSizeValue()
{
    throw dashee::Hardware::ExceptionServoController("This class is abstract");
}

/**
 * Exception is thrown when the channel is invalid
 */
void ServoController::testExceptionInvalidChannel()
{
    this->servoController->setTarget(100, 2);
}

/**
 * Exception is thrown when the target is invalid
 */
void ServoController::testExceptionInvalidPositiveTarget()
{
    this->servoController->setTarget(1, 1000);
}

/**
 * Exception is thrown when the target is invalid
 */
void ServoController::testExceptionInvalidNegativeTarget()
{
    this->servoController->setTarget(1, -1000);
}

/**
 * Exception is thrown when the target is invalid and set to a 
 * very very large number
 */
void ServoController::testExceptionInvalidLargePositiveTarget()
{
    this->servoController->setTarget(1, 100084);
}

/**
 * Exception is thrown when the target is invalid and set to a 
 * very very large negative number
 */
void ServoController::testExceptionInvalidLargeNegativeTarget()
{
    this->servoController->setTarget(1, -234128989934832);
}

/**
 * Abstract ExceptionInvalidFile
 */
void ServoController::testExceptionInvalidFile()
{
    throw dashee::Hardware::ExceptionServoController("This function is abstract");
}

/**
 * Clean up
 */
void ServoController::tearDown()
{
    delete this->servoController;
}
