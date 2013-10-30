#include "Servo/UART.h"

/**
 * Create a new instance of ServoControllerDummy and 
 * set it to the private variable
 */
void dashee::test::ServoUART::setUp()
{
    this->fd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY);

    if (this->fd != -1)
        CPPUNIT_FAIL("Cannot open file!");

    this->servo = new dashee::ServoUART(&this->fd, 1);
}

/**
 * TearDown the opened variables and call parent
 * teardown functions
 */
void dashee::test::ServoUART::tearDown()
{
    if (this->fd != -1)
        close(this->fd);

    Servo::tearDown();
}
