#include "Server.h"

/**
 * Throw an exception. because we cant have abstract classes
 * in CPPUnit this is a dumb way of doing it but it works
 *
 * @throws ExceptionServer
 */
void dashee::test::Server::setUp()
{
    throw dashee::ExceptionServoController("This class is abstract");
}

/**
 * Clean up
 */
void dashee::test::Server::tearDown()
{
    delete this->servoController;
}
