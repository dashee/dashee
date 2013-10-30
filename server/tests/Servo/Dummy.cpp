#include "Servo/Dummy.h"

/**
 * Create a new instance of ServoControllerDummy and 
 * set it to the private variable
 */
void dashee::test::ServoDummy::setUp()
{
    this->fd = fopen("data/Servo.bin", "r+b");

    if (fd == NULL)
        CPPUNIT_FAIL("Cannot open file!");

    this->servo = new dashee::ServoDummy(this->fd, 1);
}

/**
 * TearDown the opened variables and call parent
 * teardown functions
 */
void dashee::test::ServoDummy::tearDown()
{
    if (this->fd != NULL)
        fclose(this->fd);

    Servo::tearDown();
}
