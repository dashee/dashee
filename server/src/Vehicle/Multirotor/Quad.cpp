#include <dashee/Vehicle/Multirotor/Quad.h>

using namespace dashee;

/**
 * Construct and pass to its parent
 */
VehicleMultirotorQuad::VehicleMultirotorQuad(
        dashee::Hardware::ServoController * servoController, 
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
 * Nothing to do
 */
VehicleMultirotorQuad::~VehicleMultirotorQuad()
{
}
