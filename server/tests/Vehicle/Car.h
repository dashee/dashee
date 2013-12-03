/**
 * @file tests/Vehicle/Car.h
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
    virtual void testTransforQueue();
    virtual void testSetAndGetFromConfig();

public:
    // Let the derived class deal with setting up the variables
    virtual void setUp();
};

#endif
