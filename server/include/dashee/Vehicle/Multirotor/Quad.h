/**
 * @file include/dashee/Vehicle/Multirotor/Quad.h
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
            Server * server, 
            Config * conf = NULL
        );

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
    virtual void transform();

    virtual ~VehicleMultirotorQuad();
};

#endif


