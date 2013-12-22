/**
 * @file tests/Vehicle/Multirotor/Quad/X.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_TEST_MODEL_MULTIROTOR_QUAD_X_H_
#define DASHEE_TEST_MODEL_MULTIROTOR_QUAD_X_H_

#include <dashee/Vehicle/Multirotor/Quad/X.h>
#include "Vehicle/Multirotor/Quad.h"

/**
 * Set the namespace
 */
namespace dashee
{
    namespace test
    {
        class VehicleMultirotorQuadX;
    }
}

/**
 * General definitions for MultiRotorQuadX
 */
class dashee::test::VehicleMultirotorQuadX
    : public dashee::test::VehicleMultirotorQuad
{
    // Register test
    CPPUNIT_TEST_SUB_SUITE(
	    dashee::test::VehicleMultirotorQuadX,
	    dashee::test::VehicleMultirotorQuad
	);
    
    // End
    CPPUNIT_TEST_SUITE_END();

private:
protected:

    // Load values from configuration and ensure that all values are good
    virtual void testUpdate();

public:
    virtual void setUp();
};

#endif
