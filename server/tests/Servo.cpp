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
    throw dashee::ExceptionServo("This function is abstract");
}

/**
 * Go through each servo channel and set the Target.
 *
 * Once a default target is set, the system also sets the target
 * of that channel, make sure to check the actual target value is
 * changed as well
 */
void dashee::test::Servo::testSetAndGetTargetDefault()
{
    // Check the default
    CPPUNIT_ASSERT(this->servo->getTargetDefault() == 0);

    for (unsigned short int x = 0; x <= 100; x++)
    {
        // Set and check the target default, also check the getTarget
        // because setTargetDefault changes the current target value
        this->servo->setTargetDefault(x);
        CPPUNIT_ASSERT(this->servo->getTargetDefault() == x);
        CPPUNIT_ASSERT(this->servo->getTarget() == x);
    }
}

/**
 * Go through each servo channel and set the fallback value.
 *
 */
void dashee::test::Servo::testSetAndGetTargetFallback()
{
    // Check the default value
    CPPUNIT_ASSERT(this->servo->getTargetFallback() == 0);

    for (unsigned short int x = 0; x <= 100; x++)
    {
        // Set the targetfallback enabled to false so when setting target
        // fallback the flag is turned true.
        this->servo->setTargetFallbackEnabled(false);
        this->servo->setTargetFallback(x);
        CPPUNIT_ASSERT(this->servo->getTargetFallbackEnabled() == true);
        CPPUNIT_ASSERT(this->servo->getTargetFallback() == x);
    }
}

/**
 * Go through each channel and test TargetFallbackEnabled value.
 * 
 * Once a fallback value is set, the fallbackEnabled is automaticly
 * enabled. So to start with set the fallback to false, change the fallback
 * check the value of fallback and also ensure that the fallback is enabled.
 */
void dashee::test::Servo::testSetAndGetTargetFallbackEnabled()
{
    // By default it should be set to false
    CPPUNIT_ASSERT(this->servo->getTargetFallbackEnabled() == true);

    // Check false
    this->servo->setTargetFallbackEnabled(false);
    CPPUNIT_ASSERT(this->servo->getTargetFallbackEnabled() == false);
        
    // Check true
    this->servo->setTargetFallbackEnabled(true);
    CPPUNIT_ASSERT(this->servo->getTargetFallbackEnabled() == true);

    // Check flag being changed everytime setTargetFallback is called
    for (unsigned short int x = 0; x <= 100; x++)
    {
        // Reset the flag
        this->servo->setTargetFallbackEnabled(false);
        CPPUNIT_ASSERT(this->servo->getTargetFallbackEnabled() == false);

        // Change the TargetFallback and check the enabled value
        this->servo->setTargetFallback(x);
        CPPUNIT_ASSERT(this->servo->getTargetFallbackEnabled() == true);
    }
}

/**
 * Test and see weather fallbacks worked or not
 */ 
void dashee::test::Servo::testFallbackAndRevertTarget()
{
    // Call revert without any reason, just to see all works
    this->servo->revert();

    // Call fallback without any reason to make sure no exceptions are 
    // thrown
    this->servo->fallback();
    
    // Set some initial values to ensure the change
    this->servo->setTarget(5);
    this->servo->setTargetFallback(10);

    // Call fallback and check the target value
    this->servo->fallback();
    CPPUNIT_ASSERT(this->servo->getTarget() == 10);

    // Ensure that reverting brings the value back to normal
    this->servo->revert();
    CPPUNIT_ASSERT(this->servo->getTarget() == 5);

    // Ensure that reverting the second time does not mod the 
    // set value
    this->servo->setTarget(99);
    this->servo->revert();
    CPPUNIT_ASSERT(this->servo->getTarget() == 99);

    // Ensure that fallback is not activated on a given servo
    // when fallback is disabled.
    this->servo->setTargetFallbackEnabled(false);
    this->servo->fallback();
    CPPUNIT_ASSERT(this->servo->getTarget() == 99);
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
 * Exception is thrown when default target is invalid
 */
void dashee::test::Servo::testExceptionInvalidPositiveTargetDefault()
{
    this->servo->setTargetDefault(1000);
}

/**
 * Exception is thrown when default target is invalid
 */
void dashee::test::Servo::testExceptionInvalidNegativeTargetDefault()
{
    this->servo->setTargetDefault(-1000);
}

/**
 * Exception is thrown when default target is invalid
 */
void dashee::test::Servo::testExceptionInvalidLargePositiveTargetDefault()
{
    this->servo->setTargetDefault(1000084);
}

/**
 * Exception is thrown when default target is invalid
 */
void dashee::test::Servo::testExceptionInvalidLargeNegativeTargetDefault()
{
    this->servo->setTargetDefault(-2345653453456673);
}

/**
 * Exception is thrown when fallback target is invalid
 */
void dashee::test::Servo::testExceptionInvalidPositiveTargetFallback()
{
    this->servo->setTargetFallback(1000);
}

/**
 * Exception is thrown when fallback target is invalid
 */
void dashee::test::Servo::testExceptionInvalidNegativeTargetFallback()
{
    this->servo->setTargetFallback(-1000);
}

/**
 * Exception is thrown when fallback target is invalid
 */
void dashee::test::Servo::testExceptionInvalidLargePositiveTargetFallback()
{
    this->servo->setTargetFallback(1000084);
}

/**
 * Exception is thrown when fallback target is invalid
 */
void dashee::test::Servo::testExceptionInvalidLargeNegativeTargetFallback()
{
    this->servo->setTargetFallback(-2345653453456673);
}

/**
 * Clean up
 */
void dashee::test::Servo::tearDown()
{
    delete this->servo;
}
