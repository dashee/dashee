#include <dashee/Vehicle/Multirotor/Quad.h>

using namespace dashee;

/**
 * Construct and pass to its parent
 */
VehicleMultirotorQuad::VehicleMultirotorQuad(
        ServoController * servoController, 
	Config * config
    ) : VehicleMultirotor(servoController, config)
{
    this->motors.push_back(servoController->getServo(0));
    this->motors.push_back(servoController->getServo(1));
    this->motors.push_back(servoController->getServo(2));
    this->motors.push_back(servoController->getServo(3));

    if (config != NULL)
        this->loadFromConfig(config);
}

/**
 * Load properties from configuration
 *
 * @param config The configuration object
 */ 
void VehicleMultirotorQuad::loadFromConfig(Config * config)
{
    if (config->isKeySet("vehicle-multirotor-quad-m1"))
        this->motors[0] = servoController->getServo(
                config->getUInt("vehicle-multirotor-quad-m1")
            );

    if (config->isKeySet("vehicle-multirotor-quad-m2"))
        this->motors[1] = servoController->getServo(
                config->getUInt("vehicle-multirotor-quad-m2")
            );

    if (config->isKeySet("vehicle-multirotor-quad-m3"))
        this->motors[2] = servoController->getServo(
                config->getUInt("vehicle-multirotor-quad-m3")
            );

    if (config->isKeySet("vehicle-multirotor-quad-m4"))
        this->motors[3] = servoController->getServo(
                config->getUInt("vehicle-multirotor-quad-m4")
            );
    
}

/**
 * Tranform the helicopter, by reading from the input mixing
 * and then outputing to the servos
 *
 * @param server The server to transform from
 */
void VehicleMultirotorQuad::transform(Server * server)
{
    VehicleMultirotor::transform(server);

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
