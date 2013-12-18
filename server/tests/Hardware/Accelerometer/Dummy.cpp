#include "Hardware/Accelerometer/Dummy.h"

/**
 * Create a new pointer to the dummy object
 */
void dashee::test::Hardware::AccelerometerDummy::setUp()
{
    this->accelerometer = new dashee::Hardware::AccelerometerDummy();
}

/**
 * Delete the pointer to the accelerometer
 */
void dashee::test::Hardware::AccelerometerDummy::tearDown()
{
    delete this->accelerometer;
}
