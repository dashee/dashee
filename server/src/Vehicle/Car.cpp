#include <dashee/Vehicle/Car.h>

using namespace dashee;

/**
 * Constructor
 */ 
VehicleCar::VehicleCar(
        ServoController * servoController, 
	Config * config
    ) : Vehicle(servoController, config)
{
    this->setYawChannel(1);
    this->setThrottleChannel(2);

    this->setYaw(this->yaw);
    this->setThrottle(128);
    this->throttleFallback = 128;

    if (config != NULL)
        this->loadFromConfig(config);
}

/**
 * Load state from configuration.
 *
 * @param config The pointer to the configuration values
 *
 * @throws ExceptionVehicle if Config is passed as NULL
 */
void VehicleCar::loadFromConfig(Config * config)
{
    if (config == NULL)
        throw ExceptionVehicle("The config variable must not be null");

    Vehicle::loadFromConfig(config);

    if (config->isKeySet("throttle-channel"))
        this->setThrottleChannel(config->getUInt("throttle-channel"));
    if (config->isKeySet("yaw-channel"))
        this->setYawChannel(config->getUInt("yaw-channel"));
}

/**
 * Set the yaw Servo channel.
 *
 * @param channel The value of the channel to set
 *
 * @throws ExceptionVehicle if channel is outside the contraints of the servoc 
 *  controller
 */
void VehicleCar::setYawChannel(const unsigned short int channel)
{
    if (channel < 0 || channel > this->servoController->size())
        throw ExceptionVehicle("The throttle channel is invalid");

    this->yawChannel = channel;
}

/**
 * Get the yaw channel.
 *
 * @returns yaw channel.
 */
unsigned short int VehicleCar::getYawChannel()
{
    return this->yawChannel;
}


/**
 * Set the throttle Servo channel.
 *
 * @param channel The value of the channel to set
 *
 * @throws ExceptionVehicle if channel is outside the contraints of the servoc 
 *  controller
 */
void VehicleCar::setThrottleChannel(const unsigned short int channel)
{
    if (channel < 0 || channel > this->servoController->size())
        throw ExceptionVehicle("The throttle channel is invalid");

    this->throttleChannel = channel;
}

/**
 * Get the throttle channel.
 *
 * @returns throttle channel.
 */
unsigned short int VehicleCar::getThrottleChannel()
{
    return this->throttleChannel;
}

 /**
  * Set the value of yaw.
  *
  * This will set the value that represents the yaw and will also set the value 
  * on the servo.
  *
  * @param value The value to set it to.
  */
void VehicleCar::setYaw(unsigned short int value)
{
    Vehicle::setYaw(value);
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
void VehicleCar::setThrottle(unsigned short int value)
{
    Vehicle::setThrottle(value);
    this->servoController->setTarget(this->throttleChannel, value);
}

/**
 * Transform server signals to servo signals.
 *
 * A simple transformer, nothing special for the car,
 * just reads the commands that come in and sets it to
 * the relevent motor, As its is only the car model, this
 * is really a pass through
 *
 * @param Server The commands to read from
 */
void VehicleCar::transform(Server * server)
{
    Vehicle::transform(server);

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
			    server->getBufferByte(x+1)
			)
		    );
		this->setThrottle(
			static_cast<unsigned short int>(
			    server->getBufferByte(x+2)
			)
		    );

		// Add to our x value as we have delt with these bytes
		x += 2;
	    }

	    // Command that came in were wrong
	    else
		throw ExceptionVehicle("Invalid Command when transforaming");
	}
    }
}

/**
 * Destruct.
 */
VehicleCar::~VehicleCar()
{

}
