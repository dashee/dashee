#include "I2C.h"

using namespace dashee::test;

/**
 * Create a new instance of I2C
 */
void I2C::setUp()
{
    this->i2c = new dashee::I2C(1);
}

/**
 * Test contraction of I2C values by passing only numbers
 */
void I2C::testIntConstruction()
{
    dashee::I2C * i2c0 = new dashee::I2C(0);
    dashee::I2C * i2c1 = new dashee::I2C(1);

    delete i2c0;
    delete i2c1;
}

/**
 * Test constructing I2C values, by passing whole strings
 */ 
void I2C::testStringConstruction()
{
    dashee::I2C * i2c0 = new dashee::I2C("/dev/i2c-0");
    dashee::I2C * i2c1 = new dashee::I2C("/dev/i2c-1");

    delete i2c0;
    delete i2c1;
}

/**
 * Destroy the I2C interface and tear down our tests
 */
void I2C::tearDown()
{
    delete i2c;
}
