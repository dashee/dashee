#include "Hardware/Accelerometer.h"

/**
 * Fail setting up an abstract class
 */
void dashee::test::Hardware::Accelerometer::setUp()
{
    throw dashee::Exception("Cannot set up an abstract class");
}

/**
 * Test the default state of the loaded class
 */
void dashee::test::Hardware::Accelerometer::testDefaultLoad()
{

}

/**
 * Test the read function by calling read on the Accelerometer
 */
void dashee::test::Hardware::Accelerometer::testRead()
{
    CPPUNIT_ASSERT(this->accelerometer->read() == 0.0f);
}

/**
 * Fail tearing down an abstract class
 */
void dashee::test::Hardware::Accelerometer::tearDown()
{
    throw dashee::Exception("Cannot set up an abstract class");
}
