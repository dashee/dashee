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
    for (unsigned short int servos = 0; servos < 6; servos++) 
    {
        for (unsigned short int x = 0; x <= 100; x++)
        {
            this->servoController->setTarget(servos, x);
            CPPUNIT_ASSERT(this->servoController->getTarget(servos) == x);
        }
    }
}

/**
 * Go through each servo channel and set the Target.
 *
 * Once a default target is set, the system also sets the target
 * of that channel, make sure to check the actual target value is
 * changed as well
 */
void dashee::test::ServoController::testSetAndGetTargetDefault()
{
    for (unsigned short int servos = 0; servos < 6; servos++) 
    {
        for (unsigned short int x = 0; x <= 100; x++)
        {
            this->servoController->setTargetDefault(servos, x);
            CPPUNIT_ASSERT(this->servoController->getTargetDefault(servos) == x);
            CPPUNIT_ASSERT(this->servoController->getTarget(servos) == x);
        }
    }
}

/**
 * Go through each servo channel and set the fallback value.
 *
 */
void dashee::test::ServoController::testSetAndGetTargetFallback()
{
    for (unsigned short int servos = 0; servos < 6; servos++) 
    {
        for (unsigned short int x = 0; x <= 100; x++)
        {
            this->servoController->setTargetFallbackEnabled(servos, false);
            this->servoController->setTargetFallback(servos, x);
            CPPUNIT_ASSERT(this->servoController->getTargetFallbackEnabled(servos) == true);
            CPPUNIT_ASSERT(this->servoController->getTargetFallback(servos) == x);
        }
    }
}

/**
 * Go through each channel and test TargetFallbackEnabled value.
 * 
 * Once a fallback value is set, the fallbackEnabled is automaticly
 * enabled. So to start with set the fallback to false, change the fallback
 * check the value of fallback and also ensure that the fallback is enabled.
 */
void dashee::test::ServoController::testSetAndGetTargetFallbackEnabled()
{
    for (unsigned short int servos = 0; servos < 6; servos++) 
    {
        // By default it should be set to false
        CPPUNIT_ASSERT(this->servoController->getTargetFallbackEnabled(servos) == true);

        // Check false
        this->servoController->setTargetFallbackEnabled(servos, false);
        CPPUNIT_ASSERT(this->servoController->getTargetFallbackEnabled(servos) == false);
            
        // Check true
        this->servoController->setTargetFallbackEnabled(servos, true);
        CPPUNIT_ASSERT(this->servoController->getTargetFallbackEnabled(servos) == true);

        // Check flag being changed everytime setTargetFallback is called
        for (unsigned short int x = 0; x <= 100; x++)
        {
            // Reset the flag
            this->servoController->setTargetFallbackEnabled(servos, false);
            CPPUNIT_ASSERT(this->servoController->getTargetFallbackEnabled(servos) == false);

            // Change the TargetFallback and check the enabled value
            this->servoController->setTargetFallback(servos, x);
            CPPUNIT_ASSERT(this->servoController->getTargetFallbackEnabled(servos) == true);
        }
    }
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
        
    for (unsigned short int servos = 0; servos < 6; servos++) 
    {   
        // Set some initial values to ensure the change
        this->servoController->setTarget(servos, 5);
        this->servoController->setTargetFallback(servos, 10);

        // Call fallback and check the target value
        this->servoController->fallback();
        CPPUNIT_ASSERT(this->servoController->getTarget(servos) == 10);

        // Ensure that reverting brings the value back to normal
        this->servoController->revert();
        CPPUNIT_ASSERT(this->servoController->getTarget(servos) == 5);
    
        // Ensure that reverting the second time does not mod the 
        // set value
        this->servoController->setTarget(servos, 99);
        this->servoController->revert();
        CPPUNIT_ASSERT(this->servoController->getTarget(servos) == 99);

        // Ensure that fallback is not activated on a given servo
        // when fallback is disabled.
        this->servoController->setTargetFallbackEnabled(servos, false);
        this->servoController->fallback();
        CPPUNIT_ASSERT(this->servoController->getTarget(servos) == 99);
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
