/**
 * @file tests/Vehicle/Multirotor.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_TEST_MODEL_MULTIROTOR_H_
#define DASHEE_TEST_MODEL_MULTIROTOR_H_

#include <dashee/Vehicle/Multirotor.h>
#include "Vehicle.h"

/**
 * Set the namespace
 */
namespace dashee
{
    namespace test
    {
        class VehicleMultirotor;
    }
}

/**
 * General definitions for MultiRotor
 */
class dashee::test::VehicleMultirotor 
    : public dashee::test::Vehicle
{
    // Register test
    CPPUNIT_TEST_SUB_SUITE(
	    dashee::test::VehicleMultirotor,
	    dashee::test::Vehicle
	);

    CPPUNIT_TEST_EXCEPTION(
	    testInvalidMotorChannel, 
	    dashee::ExceptionOutOfBounds
	);
    
    // End
    CPPUNIT_TEST_SUITE_END();

private:
protected:

    // Test reading from the server
    virtual void testReadFromBuffer();
    virtual void testInvalidMotorChannel();

public:
};

#endif
