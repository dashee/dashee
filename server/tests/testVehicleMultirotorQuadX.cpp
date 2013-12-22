#include <dashee/Server/UDP.h>
#include <dashee/ServoController/UART.h>
#include <dashee/ServoController/USB.h>
#include <dashee/ServoController/Dummy.h>
#include "Vehicle/Multorotor/Quad/X.h"
#include "dashee.h"

CPPUNIT_TEST_SUITE_REGISTRATION(dashee::test::VehicleMultirotorQuadX);

/**
 * Load the correct values into static variables
 * and then run the test
 *
 * USAGE: $0 <ServoControllerType> <ServoControllerFile> <ServerType> 
 * <ServerPort>
 *	Where ServoControllerType: dummy, UART
 *	Where ServoControllerFile: data/Servo.bin, 
 *	Where ServerType: UDP, TCP
 *
 */
int main(int argc, char ** argv)
{
    try
    {
	if (argc != 4)
	    throw dashee::Exception("Must provide 3 arguments");

	// Load the appropriate servoController
	if (strcmp(argv[1], "dummy") == 0)
	    dashee::test::Vehicle::servoController
		= new dashee::ServoControllerDummy(argv[2], 6);

	else if (strcmp(argv[1], "UART") == 0)
	    dashee::test::Vehicle::servoController
		= new dashee::ServoControllerUART(argv[2]);

	else
	    throw dashee::Exception("Invalid ServoController");

        dashee::test::Vehicle::VEHICLE_TIMEOUT = dashee::strtol(argv[3]);

	// Run the test
	int ec = dashee::test::run();

	// Clean up
	delete dashee::test::Vehicle::servoController;

	// Return the correct error code
	return ec;
    }
    catch(dashee::Exception e)
    {
	fprintf(stderr, "Exception: %s", e.what());
    }

    return -1;
}
