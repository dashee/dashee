#include <dashee/Vehicle/Multirotor/Quad.h>

using namespace dashee;

/**
 * Construct and pass to its parent
 */
VehicleMultirotorQuad::VehicleMultirotorQuad(
        ServoController * servoController, 
        Server * server, 
	Config * config
    ) : VehicleMultirotor(servoController, server, config)
{
    this->motors.push_back(servoController->getServo(0));
    this->motors.push_back(servoController->getServo(1));
    this->motors.push_back(servoController->getServo(2));
    this->motors.push_back(servoController->getServo(3));
}


/**
 * Tranform the helicopter, by reading from the input mixing
 * and then outputing to the servos
 */
void VehicleMultirotorQuad::transform()
{
    VehicleMultirotor::transform();

    for (size_t x = 0; x < server->size(); x++)
    {
	// Control Command
	if (server->getBufferByte(x) == 0)
	{
	    // Ensure we have the correct number of bytes
	    // make sure atleast two more bytes exist
	    if (x + 4 < server->size())
	    {
                this->mix(
                        server->getBufferByte(x+1),
                        server->getBufferByte(x+2),
                        server->getBufferByte(x+3),
                        server->getBufferByte(x+4)
                    );

                x += 4;
            }
            else 
		throw ExceptionVehicle("Invalid Command when transforaming");
        }
    }
}

/**
 * Nothing to do
 */
VehicleMultirotorQuad::~VehicleMultirotorQuad()
{
}
