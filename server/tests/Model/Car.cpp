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
