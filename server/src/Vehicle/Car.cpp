#include <dashee/Vehicle/Car.h>

using namespace dashee;

/**
 * Constructor
 *
 * @param servoController Object to control servoes
 * @param config Load from configuration
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
    this->setThrottleFallback(128);

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
    if (channel > this->servoController->size())
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
    if (channel > this->servoController->size())
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
 * Read from the queue and update our model
 *
 * @param buffer The std::queue holding our values.
 */
void VehicleCar::read(Buffer<unsigned char> * buffer)
{
    while (!buffer->empty())
    {
	// Found a command byte
	if (buffer->front() == 0)
	{
	    buffer->pop();

	    // Ensure the size is still sufficent to do the next two commands
	    if (buffer->size() < 2)
		break;

	    // Set the yaw and throttle from the buffer
	    this->setYaw(static_cast<unsigned short int>(buffer->next()));
	    this->setThrottle(static_cast<unsigned short int>(buffer->next()));
	}

	// Invalid byte, continue
	else
	{
	    dashee::Log::warning(4, "Invalid command %d", buffer->front());
	    buffer->pop();
	}
    }
}

/**
 * This function sends its current state to the physical model
 */
void VehicleCar::update()
{
    this->servoController->setTarget(
	    this->getYawChannel(),
	    this->getYaw()
	);

    this->servoController->setTarget(
	    this->getThrottleChannel(), 
	    this->getThrottle()
	);
}

/**
 * Destruct.
 */
VehicleCar::~VehicleCar()
{

}
