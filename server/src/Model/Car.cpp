#include <dashee/Model/Car.h>

using namespace dashee;

/**
 * Constructor
 */ 
ModelCar::ModelCar(
        ServoController * servoController, 
        Server * server, 
	Config * config
    ) : Model(servoController, server, config)
{
    this->yawChannel = 1;
    this->throttleChannel = 2;

    this->setYaw(this->yaw);
    this->setThrottle(this->throttle);
}

/**
 * Set the value of yaw.
 *
 * This will set the value that represents the yaw
 * and will also set the value on the servo.
 *
 * @param value The value to set it to.
 */
void ModelCar::setYaw(unsigned short int value)
{
    Model::setYaw(value);
    this->servoController->setTarget(this->yawChannel, value);
}

/**
 * Set the value of the throttle.
 *
 * This will set the value that represents the throttle
 * and also set it on the servos.
 *
 * @param value The value to set it to.
 */ 
void ModelCar::setThrottle(unsigned short int value)
{
    Model::setThrottle(value);
    this->servoController->setTarget(this->throttleChannel, value);
}

/**
 * Transform server signals to servo signals.
 *
 * A simple transformer, nothing special for the car,
 * just reads the commands that come in and sets it to
 * the relevent motor, As its is only the car model, this
 * is really a pass through
 */
void ModelCar::transform()
{
    Model::transform();

    for (size_t x = 0; x < server->size(); x++)
    {
	// Control Command
	if (server->getBufferByte(x) == 0)
	{
	    // Ensure we have the correct number of bytes
	    // make sure atleast two more bytes exist
	    if (x + 2 < server->size())
	    {
		this->setYaw(
			static_cast<unsigned short int>(
			    this->server->getBufferByte(x+1)
			)
		    );
		this->setThrottle(
			static_cast<unsigned short int>(
			    this->server->getBufferByte(x+2)
			)
		    );

		// Add to our x value as we have delt with these bytes
		x += 2;
	    }

	    // Command that came in were wrong
	    else
		throw ExceptionModel("Invalid Command when transforaming");
	}
    }
}

/**
 * Destruct.
 */
ModelCar::~ModelCar()
{

}
