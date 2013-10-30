/**
 * @file tests/ServoController.h
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
 *                     you may distribute the resulting work only under a licence 
 *                     identical to this one.
 *
 * The terms and conditions are updated at http://dashee.co.uk/license. View the
 * project site for more details
 */

#ifndef DASHEE_TEST_DASHEE_H_
#define DASHEE_TEST_DASHEE_H_

#include <cppunit/TestFixture.h>
#include <cppunit/TestCase.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestResultCollector.h>

#include <dashee/common.h>
#include <dashee/Exception/OutOfBounds.h>
#include <dashee/Server/UDP.h>
#include <dashee/ServoController/UART.h>
#include <dashee/ServoController/USB.h>
#include <dashee/ServoController/Dummy.h>

#include "Config.h"
#include "GPIO.h"
#include "Model/Car.h"
#include "ServoController/Dummy.h"
#include "ServoController/UART.h"
#include "Servo/Dummy.h"
#include "Servo/UART.h"

namespace dashee
{
    namespace test
    {
        int run();
    }
}

#endif
