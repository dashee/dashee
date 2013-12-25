/**
 * @file tests/ServoController.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
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

#include <unistd.h>

// Useful for encapsulating unused variables
#define UNUSED(expr) do { (void)(expr); } while (0)

namespace dashee
{
    namespace test
    {
        int run();
    }
}

#endif
