#include "ServoController.h"

/**
 * This test will set the Servo Value, and see if the 
 * get value is correct
 *
 * @assert the values of the set servo's are the same
 */
void dashee::test::ServoController::testSetAndGetTarget()
{
    for (unsigned short int servos = 0; servos < 6; servos++) 
    {
        for (unsigned short int x = 0; x <= 100; x++)
        {
            this->servoController->setTarget(servos, x);
            CPPUNIT_ASSERT(this->servoController->getTarget(servos) == x);
        }
    }
}

void dashee::test::ServoController::testSetAndGetTargetDefault()
{

}

void dashee::test::ServoController::testSetAndGetTargetFallback()
{

}

void dashee::test::ServoController::testSetAndGetTargetFallbackEnabled()
{

}

/**
 * Test and see weather fallbacks worked or not
 */ 
void dashee::test::ServoController::testFallbackAndRevertTarget()
{
    // Call revert without any reason, just to see all works
    this->servoController->revert();

    // Call fallback without any reason to make sure no exceptions are 
    // thrown
    this->servoController->fallback();
        
    // set initial positions to something unique
    this->servoController->setTarget(0, 5);
    this->servoController->setTarget(1, 5);
    this->servoController->setTarget(2, 5);
    this->servoController->setTarget(3, 5);
    this->servoController->setTarget(4, 5);
    this->servoController->setTarget(5, 5);

    // Check to ensure that initial positions are valid
    CPPUNIT_ASSERT(this->servoController->getTarget(0) == 5);
    CPPUNIT_ASSERT(this->servoController->getTarget(1) == 5);
    CPPUNIT_ASSERT(this->servoController->getTarget(2) == 5);
    CPPUNIT_ASSERT(this->servoController->getTarget(3) == 5);
    CPPUNIT_ASSERT(this->servoController->getTarget(4) == 5);
    CPPUNIT_ASSERT(this->servoController->getTarget(5) == 5);
    
    // Set the fallbacks
    this->servoController->setTargetFallback(0, 10);
    this->servoController->setTargetFallback(1, 20);
    this->servoController->setTargetFallback(2, 30);
    this->servoController->setTargetFallback(3, 40);
    this->servoController->setTargetFallback(4, 50);
    this->servoController->setTargetFallback(5, 60);

    // Run and check fallback and see weather it worked
    this->servoController->fallback();
    CPPUNIT_ASSERT(this->servoController->getTarget(0) == 10);
    CPPUNIT_ASSERT(this->servoController->getTarget(1) == 20);
    CPPUNIT_ASSERT(this->servoController->getTarget(2) == 30);
    CPPUNIT_ASSERT(this->servoController->getTarget(3) == 40);
    CPPUNIT_ASSERT(this->servoController->getTarget(4) == 50);
    CPPUNIT_ASSERT(this->servoController->getTarget(5) == 60);

    // Run and cheack weather the reverting of the servo worked
    this->servoController->revert();
    CPPUNIT_ASSERT(this->servoController->getTarget(0) == 5);
    CPPUNIT_ASSERT(this->servoController->getTarget(1) == 5);
    CPPUNIT_ASSERT(this->servoController->getTarget(2) == 5);
    CPPUNIT_ASSERT(this->servoController->getTarget(3) == 5);
    CPPUNIT_ASSERT(this->servoController->getTarget(4) == 5);
    CPPUNIT_ASSERT(this->servoController->getTarget(5) == 5);
    
    // Call revert unnesesorily and make sure the values dont budge
    this->servoController->setTarget(0, 99);
    this->servoController->setTarget(1, 99);
    this->servoController->setTarget(2, 99);
    this->servoController->setTarget(3, 99);
    this->servoController->setTarget(4, 99);
    this->servoController->setTarget(5, 99);
    this->servoController->revert();
    CPPUNIT_ASSERT(this->servoController->getTarget(0) == 99);
    CPPUNIT_ASSERT(this->servoController->getTarget(1) == 99);
    CPPUNIT_ASSERT(this->servoController->getTarget(2) == 99);
    CPPUNIT_ASSERT(this->servoController->getTarget(3) == 99);
    CPPUNIT_ASSERT(this->servoController->getTarget(4) == 99);
    CPPUNIT_ASSERT(this->servoController->getTarget(5) == 99);
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
 * The function defined 
 */
void dashee::test::ServoController::testExceptionInvalidFile()
{
    throw dashee::ExceptionServoController("Please define this function in subclass");
}

/**
 * Throw an exception. because we cant have abstract classes
 * in CPPUnit this is a dumb way of doing it but it works
 *
 * @throws
 */
void dashee::test::ServoController::setUp()
{
    throw dashee::ExceptionServoController("This class is abstract");
}

/**
 * Clean up
 */
void dashee::test::ServoController::tearDown()
{
    delete this->servoController;
}
