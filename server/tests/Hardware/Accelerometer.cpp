#include "Hardware/Accelerometer.h"

using namespace dashee::test::Hardware;

/**
 * Fail setting up an abstract class
 */
void Accelerometer::setUp()
{
    throw dashee::Exception("Cannot set up an abstract class");
}

/**
 * Test the default state of the loaded class
 */
void Accelerometer::testDefaultLoad()
{
    throw dashee::Exception("Cannot testDefaultLoad abstract class");
}

/**
 * Test the read function by calling read on the Accelerometer
 */
void Accelerometer::testReadAndUpdate()
{
    throw dashee::Exception("Cannot testRead in an abstract class");
}

/**
 * Fail tearing down an abstract class
 */
void Accelerometer::tearDown()
{
    throw dashee::Exception("Cannot set up an abstract class");
}
