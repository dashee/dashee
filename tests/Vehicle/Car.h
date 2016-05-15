/**
 * @file tests/Vehicle/Car.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_TEST_MODEL_CAR_H_
#define DASHEE_TEST_MODEL_CAR_H_

#include <dashee/Vehicle/Car.h>
#include "Vehicle.h"

/**
 * Set the namespace
 */
namespace dashee
{
    namespace test
    {
        class VehicleCar;
    }
}

/**
 * VehicleCar test class for
 * unit testing known components
 */
class dashee::test::VehicleCar : public dashee::test::Vehicle
{
    // Register test
    CPPUNIT_TEST_SUB_SUITE(
	    dashee::test::VehicleCar,
	    dashee::test::Vehicle
	);
    
    // End
    CPPUNIT_TEST_SUITE_END();

private:
protected:
    virtual void testSetAndGetThrottle();
    virtual void testReadFromBuffer();
    virtual void testUpdate();

public:
    // Let the derived class deal with setting up the variables
    virtual void setUp();
};

#endif
