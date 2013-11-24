#include "Vehicle/Car.h"

/**
 * Start up
 */ 
void dashee::test::VehicleCar::setUp()
{
    dashee::test::Vehicle::setUp();

    this->vehicle = new dashee::VehicleCar(
	    (dashee::ServoController *)dashee::test::Vehicle::servoController 
	);

    dashee::VehicleCar * temp 
        = static_cast<dashee::VehicleCar *>(this->vehicle);

    temp->setThrottleChannel(2);
    temp->setYawChannel(4);
}

/**
 * Overwrite our throttle function because it starts from 128
 * for our car
 */ 
void dashee::test::VehicleCar::testSetAndGetThrottle()
{
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 128);

    for (int x = 0; x < 256; x++)
    {
	this->vehicle->setThrottle(x);
	CPPUNIT_ASSERT(this->vehicle->getThrottle() == x);
	sleep();
    }
    
    for (int x = 255; x >= 0; x--)
    {
	this->vehicle->setThrottle(x);
	CPPUNIT_ASSERT(this->vehicle->getThrottle() == x);
        sleep();
    }
    
    // Reset the throttle
    this->vehicle->setThrottle(0);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 0);
    sleep();
}

/**
 * Create a dummy configuration file, and let our vehicle set the state from the
 * read configuration
 */
void dashee::test::VehicleCar::testSetAndGetFromConfig()
{
    dashee::VehicleCar * vehicleCar = new dashee::VehicleCar(
	    this->vehicle->getServoController()
	);

    dashee::Config * config = new Config();
    config->set("yaw-channel", 3);
    config->set("throttle-channel", 4);

    vehicleCar->loadFromConfig(config);

    CPPUNIT_ASSERT(vehicleCar->getYawChannel() == 3);
    CPPUNIT_ASSERT(vehicleCar->getThrottleChannel() == 4);

    delete config;
    delete vehicleCar;
}
