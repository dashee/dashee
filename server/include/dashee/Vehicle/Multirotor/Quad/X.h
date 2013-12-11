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

public:
    // Construct and pass through to parent
    VehicleMultirotorQuadX(
            ServoController * servoController, 
            Config * conf = NULL
        );

    // Update our physical model
    virtual void update();

    virtual ~VehicleMultirotorQuadX();
};

#endif
