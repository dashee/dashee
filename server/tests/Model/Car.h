/**
 * @file tests/Model/Car.h
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

#include <dashee/Model/Car.h>
#include "Model.h"

/**
 * Set the namespace
 */
namespace dashee
{
    namespace test
    {
        class ModelCar;
    }
}

/**
 * ModelCar test class for
 * unit testing known components
 */
class dashee::test::ModelCar : public dashee::test::Model
{
    // Register test
    CPPUNIT_TEST_SUB_SUITE(
	    dashee::test::ModelCar,
	    dashee::test::Model
	);
    
    // End
    CPPUNIT_TEST_SUITE_END();

private:
protected:
    virtual void testSetAndGetThrottle();

public:
    // Let the derived class deal with setting up the variables
    virtual void setUp();
};

#endif
