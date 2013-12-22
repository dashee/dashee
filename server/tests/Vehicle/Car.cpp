#include "Vehicle/Car.h"

using namespace dashee::test;

/**
 * Start up
 */ 
void VehicleCar::setUp()
{
    Vehicle::setUp();

    this->vehicle = new dashee::VehicleCar(
	    (dashee::ServoController *)Vehicle::servoController 
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
void VehicleCar::testSetAndGetThrottle()
{
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 128);

    for (int x = 0; x < 256; x++)
    {
	this->vehicle->setThrottle(x);
	CPPUNIT_ASSERT(this->vehicle->getThrottle() == x);
	dashee::sleep(VEHICLE_TIMEOUT);
    }
    
    for (int x = 255; x >= 0; x--)
    {
	this->vehicle->setThrottle(x);
	CPPUNIT_ASSERT(this->vehicle->getThrottle() == x);
        dashee::sleep(VEHICLE_TIMEOUT);
    }
    
    // Reset the throttle
    this->vehicle->setThrottle(0);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 0);
    dashee::sleep(VEHICLE_TIMEOUT);
}

/**
 * Call transform on a static queue
 */ 
void VehicleCar::testReadFromBuffer()
{
    dashee::Buffer<unsigned char> q;
    
    // Push one command and see the status
    q.push(0);
    q.push(0);
    q.push(0);
    this->vehicle->read(&q);
    CPPUNIT_ASSERT(this->vehicle->getYaw() == 0);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 0);
    CPPUNIT_ASSERT(q.empty() == true);

    // Push another command and see the changed
    q.push(0);
    q.push(10);
    q.push(10);
    this->vehicle->read(&q);
    CPPUNIT_ASSERT(this->vehicle->getYaw() == 10);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 10);
    CPPUNIT_ASSERT(q.empty() == true);

    // Push two commands and check that the values are set to the
    // last known value
    q.push(0);
    q.push(20);
    q.push(20);
    q.push(0);
    q.push(30);
    q.push(30);
    this->vehicle->read(&q);
    CPPUNIT_ASSERT(this->vehicle->getYaw() == 30);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 30);
    CPPUNIT_ASSERT(q.empty() == true);

    // Test invalid set of commands
    q.push(10);
    q.push(11);
    q.push(12);
    this->vehicle->read(&q);
    CPPUNIT_ASSERT(this->vehicle->getYaw() == 30);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 30);
    CPPUNIT_ASSERT(q.empty() == true);

    // Test invalid set of commands
    q.push(10);
    q.push(11);
    q.push(12);
    q.push(0);
    q.push(40);
    q.push(40);
    q.push(10);
    this->vehicle->read(&q);
    CPPUNIT_ASSERT(this->vehicle->getYaw() == 40);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 40);
    CPPUNIT_ASSERT(q.empty() == true);
    
    CPPUNIT_ASSERT(this->vehicle->getYaw() != 255);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() != 255);
}

/**
 * Test the changes from the motor it self
 */
void VehicleCar::testUpdate()
{
    dashee::ServoController * servoController 
        = this->vehicle->getServoController();

    dashee::VehicleCar * vehicleCar 
        = static_cast<dashee::VehicleCar *>(this->vehicle);

    vehicleCar->setYaw(10);
    vehicleCar->setThrottle(11);
    vehicleCar->update();

    CPPUNIT_ASSERT(
            servoController->getTarget(vehicleCar->getYawChannel()) == 10
        );
    CPPUNIT_ASSERT(
            servoController->getTarget(
                vehicleCar->getThrottleChannel()
            ) == 11
        );
}

/**
 * Create a dummy configuration file, and let our vehicle set the state from the
 * read configuration
 */
void VehicleCar::testSetAndGetFromConfig()
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
