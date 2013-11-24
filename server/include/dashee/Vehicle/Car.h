/**
 * @file include/dashee/Vehicle/Car.h
 * @author Shahmir Javaid
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. In general
 * you are free to copy, distribute, display, and perform the work, 
 * you are also free to make derivative works, under the following conditions:
 *  - Attribution    — You must give dashee's author credit.
 *  - Non-Commercial - You may not use this dashee for commercial 
 *                     purposes without permission.
 *  - Share Alike    — If you alter, transform, or build upon this work, 
 *                     you may distribute the resulting work only under a 
 *                     licence identical to this one.
 *
 * The terms and conditions are updated at http://dashee.co.uk/license. View the
 * project site for more details
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

    virtual ~VehicleCar();
};

#endif
