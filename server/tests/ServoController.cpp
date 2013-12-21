#include "ServoController.h"

/**
 * Throw an exception. because we cant have abstract classes
 * in CPPUnit this is a dumb way of doing it but it works
 *
 * @throws ExceptionServoController
 */
void dashee::test::ServoController::setUp()
{
    throw dashee::ExceptionServoController("This class is abstract");
}

/**
 * This test will set the Servo Value, and see if the 
 * get value is correct
 *
 * @assert the values of the set servo's are the same
 */
void dashee::test::ServoController::testSetAndGetTarget()
{   
    unsigned int timeout = 15;
    if (dynamic_cast<ServoControllerUART *>(this->servoController) == NULL)
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
 * Checks the size of the servo value.
 *
 * @throws ExceptionServoController
 */ 
void dashee::test::ServoController::testSizeValue()
{
    throw dashee::ExceptionServoController("This class is abstract");
}

/**
 * Exception is thrown when the channel is invalid
 */
void dashee::test::ServoController::testExceptionInvalidChannel()
{
    this->servoController->setTarget(100, 2);
}

/**
 * Exception is thrown when the target is invalid
 */
void dashee::test::ServoController::testExceptionInvalidPositiveTarget()
{
    this->servoController->setTarget(1, 1000);
}

/**
 * Exception is thrown when the target is invalid
 */
void dashee::test::ServoController::testExceptionInvalidNegativeTarget()
{
    this->servoController->setTarget(1, -1000);
}

/**
 * Exception is thrown when the target is invalid and set to a 
 * very very large number
 */
void dashee::test::ServoController::testExceptionInvalidLargePositiveTarget()
{
    this->servoController->setTarget(1, 100084);
}

/**
 * Exception is thrown when the target is invalid and set to a 
 * very very large negative number
 */
void dashee::test::ServoController::testExceptionInvalidLargeNegativeTarget()
{
    this->servoController->setTarget(1, -234128989934832);
}

/**
 * Abstract ExceptionInvalidFile
 */
void dashee::test::ServoController::testExceptionInvalidFile()
{
    throw dashee::ExceptionServoController("This function is abstract");
}

/**
 * Clean up
 */
void dashee::test::ServoController::tearDown()
{
    delete this->servoController;
}
