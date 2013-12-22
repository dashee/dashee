#include "Vehicle/Multirotor/Quad.h"

using namespace dashee::test;

/**
 * Set the motor channel from config, and make sure no exceptions
 * are thrown
 */
void VehicleMultirotorQuad::testSetAndGetFromConfig()
{
    dashee::Config config;

    config.set("vehicle-multirotor-m1", 2);
    config.set("vehicle-multirotor-m2", 4);
    config.set("vehicle-multirotor-m3", 6);
    config.set("vehicle-multirotor-m4", 8);

    this->vehicle->loadFromConfig(&config);
}
