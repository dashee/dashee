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

    short int m1 = 128;
    short int m2 = 128;
    short int m3 = 128;
    short int m4 = 128;

    // In a quad if there is no throttle, no point continuing
    if (this->getThrottle() == 0)
    {
	/*
        this->motors[0]->setTarget(0);
        this->motors[1]->setTarget(0);
        this->motors[2]->setTarget(0);
        this->motors[3]->setTarget(0);
        return;
	*/
    }

    m1 -= this->getPitch()-128;
    m2 -= this->getPitch()-128;
    m3 += this->getPitch()-128;
    m4 += this->getPitch()-128;
    
    m1 += this->getRoll()-128;
    m2 -= this->getRoll()-128;
    m3 -= this->getRoll()-128;
    m4 += this->getRoll()-128;

    if (m1 < 0)
	m1 = 0;
    else if (m1 > 255)
	m1 = 255;

    if (m2 < 0)
	m2 = 0;
    else if (m2 > 255)
	m2 = 255;

    if (m3 < 0)
	m3 = 0;
    else if (m3 > 255)
	m3 = 255;

    if (m4 < 0)
	m4 = 0;
    else if (m4 > 255)
	m4 = 255;

    float m1perc = m1 / 255.0f;
    float m2perc = m2 / 255.0f;
    float m3perc = m3 / 255.0f;
    float m4perc = m4 / 255.0f;

    this->motors[0]->setTarget(m1);
    this->motors[1]->setTarget(m2);
    this->motors[2]->setTarget(m3);
    this->motors[3]->setTarget(m4);

    Log::info(4, "T %3d    M %3d %3d %3d %3d    P %f %f %f %f", 
	    this->getThrottle(),
	    (int)floor(m1perc * this->getThrottle()), 
	    (int)floor(m2perc * this->getThrottle()), 
	    (int)floor(m3perc * this->getThrottle()), 
	    (int)floor(m4perc * this->getThrottle()),
	    m1perc, m2perc, m3perc, m4perc
	);
}

/**
 * Nothing to do
 */
VehicleMultirotorQuadX::~VehicleMultirotorQuadX()
{
}

