/**
 * @file include/dashee/Vehicle/Multirotor/Quad.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license.  
 */
#ifndef DASHEE_MODEL_MULTIROTOR_QUAD_H_
#define DASHEE_MODEL_MULTIROTOR_QUAD_H_

#include <dashee/Vehicle/Multirotor.h>

namespace dashee
{
    class VehicleMultirotorQuad;
}

/**
 * Virtual Vehicle class.
 *
 * This is the car class, and holds only information
 * about Throttle and Steering
 */
class dashee::VehicleMultirotorQuad : public dashee::VehicleMultirotor
{
protected:

    // Construct and pass through to parent
    VehicleMultirotorQuad(
            ServoController * servoController, 
            Config * conf = NULL
        );

    // Overwrite the loadFromConfig and set the channel values
    virtual void loadFromConfig(Config * config);

    // Function that mixes our input from the user to the
    // motor value
    virtual void mix(
            const unsigned short int pitch,
            const unsigned short int roll,
            const unsigned short int yaw,
            const unsigned short int throttle
        ) = 0;

public:

    // Transform the user input into 
    virtual void transform(Server * server);
    virtual void transform(std::queue<unsigned char> * q);

    virtual ~VehicleMultirotorQuad();
};

#endif


