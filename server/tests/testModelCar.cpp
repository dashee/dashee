#include "dashee.h"

CPPUNIT_TEST_SUITE_REGISTRATION(dashee::test::ModelCar);

/**
 * Load the correct values into static variables
 * and then run the test
 *
 * USAGE: $0 <ServoControllerType> <ServoControllerFile> <ServerType> <ServerPort>
 *	Where ServoControllerType: dummy, UART
 *	Where ServoControllerFile: data/Servo.bin, 
 *	Where ServerType: UDP, TCP
 *
 */
int main(int argc, char ** argv)
{
    try
    {
	if (argc != 5)
	    throw dashee::Exception("Must provide 4 arguments");

	// Load the appropriate servoController
	if (strcmp(argv[1], "dummy") == 0)
	    dashee::test::Model::servoController
		= new dashee::ServoControllerDummy(argv[2], 6);

	else if (strcmp(argv[1], "UART") == 0)
	    dashee::test::Model::servoController
		= new dashee::ServoControllerUART(argv[2]);

	else
	    throw dashee::Exception("Invalid ServoController");

	// Load the appropriate server
	if (strcmp(argv[3], "UDP") == 0)
	    dashee::test::Model::server 
		= new dashee::ServerUDP(dashee::strtol(argv[4]));
	else
	    throw dashee::Exception("Invalid Server");


	// Run the test
	int ec = dashee::test::run();

	// Clean up
	delete dashee::test::Model::servoController;
	delete dashee::test::Model::server;

	// Return the correct error code
	return ec;
    }
    catch(dashee::Exception e)
    {
	fprintf(stderr, "Exception: %s", e.what());
    }

    return -1;
}
