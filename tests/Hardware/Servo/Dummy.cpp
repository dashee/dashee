#include "Hardware/Servo/Dummy.h"

using namespace dashee::test::Hardware;

/**
 * Create a new instance of ServoControllerDummy and 
 * set it to the private variable
 */
void ServoDummy::setUp()
{
    this->fd = fopen("data/Servo.bin", "r+b");

    if (fd == NULL)
        CPPUNIT_FAIL("Cannot open file!");

    this->servo = new dashee::Hardware::ServoDummy(this->fd, 1);
}

/**
 * TearDown the opened variables and call parent
 * teardown functions
 */
void ServoDummy::tearDown()
{
    if (this->fd != NULL)
        fclose(this->fd);

    Servo::tearDown();
}
