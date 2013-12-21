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
    CPPUNIT_ASSERT(i2c0->getSlaveAddress() == 0x00);
    dashee::I2C * i2c1 = new dashee::I2C(1);
    CPPUNIT_ASSERT(i2c1->getSlaveAddress() == 0x00);

    delete i2c0;
    delete i2c1;

    // Check the slave address post construction
    for (unsigned char x = 0; x < 128; ++x)
    {
	dashee::I2C i2c0(0, x);
	CPPUNIT_ASSERT(i2c0.getSlaveAddress() == x);
	
	dashee::I2C i2c1(1, x);
	CPPUNIT_ASSERT(i2c1.getSlaveAddress() == x);
    }	
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
    
    // Check the slave address post construction
    for (unsigned char x = 0; x < 128; ++x)
    {
	dashee::I2C i2c0("/dev/i2c-0", x);
	CPPUNIT_ASSERT(i2c0.getSlaveAddress() == x);
	
	dashee::I2C i2c1("/dev/i2c-1", x);
	CPPUNIT_ASSERT(i2c1.getSlaveAddress() == x);
    }	
}

/**
 * Test setting and getting of the addresses, Note that only 255 addresses
 * are allowed
 */
void I2C::testSetAndGetAddress()
{
    CPPUNIT_ASSERT(this->i2c->getSlaveAddress() == 0x00);

    for (int x = 0; x < 128; ++x)
    {
	this->i2c->setSlaveAddress(static_cast<unsigned char>(x));
	CPPUNIT_ASSERT(
		this->i2c->getSlaveAddress() == static_cast<unsigned char>(x)
	    );
    }
}

/**
 * Make sure this does not throw an exception
 */
void I2C::testSet10BitAddressFlag()
{
    this->i2c->set10BitAddress(true);
    this->i2c->set10BitAddress(false);
}

/**
 * Invalid addresses should throw exceptions
 */
void I2C::testInvalidAddress()
{
    this->i2c->setSlaveAddress(0xFF);
}

/**
 * Destroy the I2C interface and tear down our tests
 */
void I2C::tearDown()
{
    delete i2c;
}
