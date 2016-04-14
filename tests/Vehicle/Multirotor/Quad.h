/**
 * @file tests/Vehicle/Multirotor/Quad.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_TEST_MODEL_MULTIROTOR_QUAD_H_
#define DASHEE_TEST_MODEL_MULTIROTOR_QUAD_H_

#include <dashee/Vehicle/Multirotor/Quad.h>
#include "Vehicle/Multirotor.h"

/**
 * Set the namespace
 */
namespace dashee
{
    namespace test
    {
        class VehicleMultirotorQuad;
    }
}

/**
 * General definitions for MultiRotorQuads
 */
class dashee::test::VehicleMultirotorQuad 
    : public dashee::test::VehicleMultirotor
{
    // Register test
    CPPUNIT_TEST_SUB_SUITE(
	    dashee::test::VehicleMultirotorQuad,
	    dashee::test::VehicleMultirotor
	);
    
    // End
    CPPUNIT_TEST_SUITE_END();

private:
protected:

    // Load values from configuration and ensure that all values are good
    virtual void testSetAndGetFromConfig();
    virtual void testInvalidMotorChannel();

public:
};

#endif
