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
 * Do some mixing for the Quadcopter, and then send the output
 * to our physical model
 */
void VehicleMultirotorQuadX::update()
{
    short int m1 = this->getThrottle();
    short int m2 = this->getThrottle();
    short int m3 = this->getThrottle();
    short int m4 = this->getThrottle();

    // {1, 1, -1, -1}
    short int pitchTranslate = static_cast<short int>(this->getPitch()-128);
    m1 += pitchTranslate;
    m2 += pitchTranslate;
    m3 -= pitchTranslate;
    m4 -= pitchTranslate;
    
    // {1, -1, -1, 1}
    short int rollTranslate = static_cast<short int>(this->getRoll()-128);
    m1 += rollTranslate;
    m2 -= rollTranslate;
    m3 -= rollTranslate;
    m4 += rollTranslate;

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

    this->motors[0]->setTarget(m1);
    this->motors[1]->setTarget(m2);
    this->motors[2]->setTarget(m3);
    this->motors[3]->setTarget(m4);

    Log::info(
	    10, 
	    "T %3d - M %3d %3d %3d %3d",
	    this->getThrottle(), m1, m2, m3, m4
	);
}

/**
 * Nothing to do
 */
VehicleMultirotorQuadX::~VehicleMultirotorQuadX()
{
}

