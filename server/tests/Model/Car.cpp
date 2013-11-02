#include "Model/Car.h"

/**
 * Start up
 */ 
void dashee::test::ModelCar::setUp()
{
    dashee::test::Model::setUp();

    this->model = new dashee::ModelCar(
	    (dashee::ServoController *)dashee::test::Model::servoController, 
	    (dashee::Server *)dashee::test::Model::server
	);
}

/**
 * Overwrite our throttle function because it starts from 128
 * for our car
 */ 
void dashee::test::ModelCar::testSetAndGetThrottle()
{
    CPPUNIT_ASSERT(this->model->getThrottle() == 128);

    for (int x = 0; x < 256; x++)
    {
	this->model->setThrottle(x);
	CPPUNIT_ASSERT(this->model->getThrottle() == x);
        usleep(MODEL_TIMEOUT);
    }
    
    // Reset the throttle
    this->model->setThrottle(0);
    CPPUNIT_ASSERT(this->model->getThrottle() == 0);
    usleep(MODEL_TIMEOUT);

    for (int x = 0; x < 256; x=x+8)
    {
	this->model->setYaw(x);
	CPPUNIT_ASSERT(this->model->getYaw() == x);
        usleep(MODEL_TIMEOUT);
    }

    // Reset the throttle
    this->model->setThrottle(0);
    CPPUNIT_ASSERT(this->model->getThrottle() == 0);
    usleep(MODEL_TIMEOUT);
}
