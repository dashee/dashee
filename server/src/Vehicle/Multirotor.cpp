#include <dashee/Vehicle/Multirotor.h>

using namespace dashee;

/**
 * Construct and pass to its parent
 *
 * Build the motors array, as multirotor
 */
VehicleMultirotor::VehicleMultirotor(
        ServoController * servoController, 
        Server * server, 
	Config * config
    ) : Vehicle(servoController, server, config)
{
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
    this->motors[motorNumber] = this->servoController->getServo(servoChannel);
}

/**
 * Nothing to do
 */
VehicleMultirotor::~VehicleMultirotor()
{
}
