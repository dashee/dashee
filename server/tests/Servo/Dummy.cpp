#include "Servo/Dummy.h"

/**
 * Create a new instance of ServoControllerDummy and 
 * set it to the private variable
 */
void dashee::test::ServoDummy::setUp()
{
    this->fd = fopen("data/Servo.bin", "r+b");

    if (fd == NULL)
        throw ExceptionServo("Cannot open file");

    this->servo = new dashee::ServoDummy(this->fd, 1);
}

/**
 * TearDown the opened variables and call parent
 * teardown functions
 */
void dashee::test::ServoDummy::tearDown()
{
    fclose(this->fd);
    Servo::tearDown();
}

/**
 * Test the size command
 */
void dashee::test::ServoDummy::testSetAndGetTarget()
{
    for (int x = 0; x <= 100; x++)
    {
        this->servo->setTarget(x);
        CPPUNIT_ASSERT(this->servo->getTarget() == x);
    }
}
