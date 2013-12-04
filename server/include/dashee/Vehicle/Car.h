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
protected:
    unsigned short int throttleChannel;
    unsigned short int yawChannel;

public:

    // Construct and pass through to parent
    VehicleCar(
        ServoController * servoController, 
        Config * conf = NULL
    );

    // Overwrite the loadFromConfig and set the channel values
    virtual void loadFromConfig(Config * config);

    // Overwrite our basic
    virtual void setThrottle(unsigned short int value);
    virtual void setYaw(unsigned short int value);
    
    // Overwrite our basic
    void setYawChannel(const unsigned short int value);
    unsigned short int getYawChannel();
    void setThrottleChannel(const unsigned short int value);
    unsigned short int getThrottleChannel();
        
    virtual void transform(Server * server);
    virtual void transform(std::queue<unsigned char> * q);

    virtual ~VehicleCar();
};

#endif
