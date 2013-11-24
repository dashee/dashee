#include <dashee/Vehicle/Multirotor/Quad/X.h>

using namespace dashee;

/**
 * Construct and pass to its parent
 */
VehicleMultirotorQuadX::VehicleMultirotorQuadX(
        ServoController * servoController, 
	Config * config
    ) : VehicleMultirotorQuad(servoController, config)
{
}

/**
 * Do some mixing for the Quadcopter
 *
 * @param pitch The pitch value
 * @param roll The roll value
 * @param yaw The yaw value
 * @param throttle The throttle value
 */
void VehicleMultirotorQuadX::mix(
        const unsigned short int pitch,
        const unsigned short int roll,
        const unsigned short int yaw,
        const unsigned short int throttle
    )
{
    this->setPitch(pitch);
    this->setRoll(roll);
    this->setYaw(yaw);
    this->setThrottle(throttle);

    // In a quad if there is no throttle, no point continuing
    if (this->getThrottle() == 0)
    {
        this->motors[0]->setTarget(0);
        this->motors[1]->setTarget(0);
        this->motors[2]->setTarget(0);
        this->motors[3]->setTarget(0);
        return;
    }

    this->motors[0]->setTarget(this->getThrottle());
    this->motors[1]->setTarget(this->getThrottle());
    this->motors[2]->setTarget(this->getThrottle());
    this->motors[3]->setTarget(this->getThrottle());
}

/**
 * Nothing to do
 */
VehicleMultirotorQuadX::~VehicleMultirotorQuadX()
{
}

