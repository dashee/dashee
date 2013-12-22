#include "Vehicle/Multirotor/Quad/X.h"

using namespace dashee::test;

/**
 * Create a new instance of the VehicleMultirotorQuadX
 */ 
void VehicleMultirotorQuadX::setUp()
{
    Vehicle::setUp();

    dashee::VehicleMultirotorQuadX * temp 
	= new dashee::VehicleMultirotorQuadX(Vehicle::servoController);

    temp->changeServoMotor(0, 2);
    temp->changeServoMotor(1, 4);
    temp->changeServoMotor(2, 6);
    temp->changeServoMotor(3, 8);

    this->vehicle = temp;
}

/**
 * Test the update function
 */
void VehicleMultirotorQuadX::testUpdate()
{

}
