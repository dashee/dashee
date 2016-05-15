/**
 * @file include/dashee/Vehicle/Car.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */
#ifndef DASHEE_MODEL_CAR_H_
#define DASHEE_MODEL_CAR_H_

#include <dashee/Vehicle.h>

namespace dashee
{
    class VehicleCar;
}

/**
 * Virtual Vehicle class.
 *
 * This is the car class, and holds only information
 * about Throttle and Steering
 */
class dashee::VehicleCar : public dashee::Vehicle
{

public:

    // Construct and pass through to parent
    VehicleCar(
        dashee::Hardware::ServoController * servoController, 
        Config * conf = NULL
    );
    
    // Update our model from a buffer
    virtual void read(Buffer<unsigned char> * buffer);

    virtual ~VehicleCar();
};

#endif
