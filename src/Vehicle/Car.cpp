#include <dashee/Vehicle/Car.h>

using namespace dashee;

/**
 * Constructor
 *
 * @param servoController Object to control servos
 * @param config Load from configuration
 */ 
VehicleCar::VehicleCar(
        dashee::Hardware::ServoController * servoController, 
	Config * config
    ) : Vehicle(servoController, config)
{
    this->setYawChannel(1);
    this->setThrottleChannel(2);

    if (config != NULL)
        this->loadFromConfig(config);
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

            // Ensure the size is still sufficient to do the next two commands
            if (buffer->size() < 2)
                break;

            // Set the yaw and throttle from the buffer
            this->setPitch(static_cast<unsigned short int>(buffer->next()));
            this->setRoll(static_cast<unsigned short int>(buffer->next()));
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
 * Destruct.
 */
VehicleCar::~VehicleCar()
{

}
