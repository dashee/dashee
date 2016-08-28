#include <dashee/Vehicle/Multirotor.h>

using namespace dashee;

/**
 * Construct and pass to its parent
 *
 * Build the motors array, as multirotor
 */
VehicleMultirotor::VehicleMultirotor(
        dashee::Hardware::ServoController * servoController, 
	Config * config
    ) : Vehicle(servoController, config)
{
    this->setThrottleFallback(0);
}

/**
 * Change the servo that the given motor represent
 *
 * There may be a case where a motor might be on a different channel, to do this
 * we allow the user to change which motor represents which Physical Motor.
 *
 * @param motorNumber - The number of the motor to change
 * @param servoChannel - The channel of servo to represent this servo
 */
void VehicleMultirotor::changeServoMotor(
        const unsigned short int motorNumber,
        const unsigned short int servoChannel
    )
{
    if (motorNumber >= this->motors.size())
	throw ExceptionOutOfBounds("Invalid motor number");

    this->motors[motorNumber] = &this->servoController->getServo(servoChannel);
}

/**
 * Read from the input, and change the model
 *
 * @param buffer The queue from which to read and clear as read
 */
void VehicleMultirotor::read(Buffer<unsigned char> * buffer)
{
    while (!buffer->empty())
    {
	// Found a command byte
	if (buffer->front() == 0)
	{
	    buffer->pop();

	    // Ensure the size is still sufficient to do the next two commands
	    if (buffer->size() < 4)
		break;

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
 * Nothing to do
 */
VehicleMultirotor::~VehicleMultirotor()
{
}
