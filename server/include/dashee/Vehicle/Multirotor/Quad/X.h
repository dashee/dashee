/**
 * @file include/dashee/Vehicle/Multirotor/Quad/X.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */
#ifndef DASHEE_MODEL_MULTIROTOR_QUAD_X_H_
#define DASHEE_MODEL_MULTIROTOR_QUAD_X_H_

#include <dashee/Vehicle/Multirotor/Quad.h>

namespace dashee
{
    class VehicleMultirotorQuadX;
}

/**
 * Quadcopter with an X setting 
 *
 * This class holds information about the current model state and also mixes
 * the values from the input
 */
class dashee::VehicleMultirotorQuadX : public dashee::VehicleMultirotorQuad
{
protected:

    // Function that mixes our input from the user to the
    // motor value
    virtual void mix(
            const unsigned short int pitch,
            const unsigned short int roll,
            const unsigned short int yaw,
            const unsigned short int throttle
        );

public:
    // Construct and pass through to parent
    VehicleMultirotorQuadX(
            ServoController * servoController, 
            Config * conf = NULL
        );


    virtual ~VehicleMultirotorQuadX();
};

#endif
