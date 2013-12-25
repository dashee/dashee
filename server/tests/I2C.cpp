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
 * This test the reading the value from the register, of our accelerometer
 * we need an actual device to perform this action as dummy devices would not 
 * do. And for that we use the 9DOF accelerometer. 
 */
void I2C::testReadRegister()
{
    // Talk to the accelerometer
    this->i2c->setSlaveAddress(0x53);

    // Create a new instance of the vector which will store the values
    std::vector<unsigned char> val;

    // Read val.size bytes from the register
    this->i2c->read(0x00, &val, 1);
    CPPUNIT_ASSERT(val.size() == 1);
    CPPUNIT_ASSERT(val[0] == 229);

    // Read 1 byte from the register
    this->i2c->read(0x00, &val, 1);
    CPPUNIT_ASSERT(val.size() == 1);
    CPPUNIT_ASSERT(val[0] == 229);
    
    // Make sure the vector only overwrites from 0th element and leaves the 
    // vector size intact to its size before it was passed to read
    val.push_back(47);
    CPPUNIT_ASSERT(val.size() == 2);
    this->i2c->read(0x00, &val, 1);
    CPPUNIT_ASSERT(val.size() == 2);
    CPPUNIT_ASSERT(val[0] == 229);
    CPPUNIT_ASSERT(val[1] == 47);

    // Make sure the vector is correctly resized
    std::vector<unsigned char> emptyval;
    CPPUNIT_ASSERT(emptyval.size() == 0);
    this->i2c->read(0x00, &emptyval, 1);
    CPPUNIT_ASSERT(emptyval.size() == 1);
}

/**
 * Write to the register and test it's values by reading them
 */
void I2C::testWriteRegister()
{
    // Talk to the accelerometer
    this->i2c->setSlaveAddress(0x53);
    
    std::vector<unsigned char> wbuffer(1, 0x00);
    std::vector<unsigned char> rbuffer(1, 0x00);

    // Get the value of the existing buffer
    this->i2c->read(0x31, &rbuffer, 1);

    // Clear the first 4 bits, so values such as ----1111 become
    // ----0000 where the dash represents the old bits we don't want to change
    rbuffer[0] = rbuffer[0] & ~0x0F;

    // Write to the first 4 bits and set the value to ----0001
    wbuffer[0] = rbuffer[0] | 0x01;

    // Write to our register, the new value
    this->i2c->write(0x31, &wbuffer);

    // Read the set value from our buffer, but before we do ensure the clear it
    rbuffer.clear();
    this->i2c->read(0x31, &rbuffer, 1);
    
    // When asserting we want to assert that the value is 0x01 on the right side
    CPPUNIT_ASSERT((rbuffer[0] & 0x0F) == 0x01);
    
    // Just like before, except this time set it to 0x02, and test the written
    // value read back from the device
    rbuffer[0] = rbuffer[0] & ~0x0F;
    wbuffer[0] = rbuffer[0] | 0x02;
    this->i2c->write(0x31, &wbuffer);
    this->i2c->read(0x31, &rbuffer, 1);
    CPPUNIT_ASSERT((rbuffer[0] & 0x0F) == 0x02);
}

/**
 * Ensure this throws an exception as we are trying to read 0 bytes
 */
void I2C::testInvalidByteSizeWhenReading()
{
    std::vector<unsigned char> buffer;
    this->i2c->read(0x31, &buffer, 0);
}

/**
 * Ensure this throws an exception as we are trying to write 0 bytes
 */
void I2C::testInvalidByteSizeWhenWriting()
{
    std::vector<unsigned char> x;
    this->i2c->write(0x31, &x, 0);
}

/**
 * If you are trying to write more bytes than you should in a buffer,
 * make sure you fail by throwing an OutOfBounds exception
 */
void I2C::testInvalidOutOfBoundsWhenWriting()
{
    std::vector<unsigned char> x;
    this->i2c->write(0x31, &x, 10);
}

/**
 * Invalid addresses should throw exceptions
 */
void I2C::testInvalidAddress()
{
    this->i2c->setSlaveAddress(0xFF);
}

/**
 * Ensure that an exception is thrown when a Null pointer for buffer is 
 * passed as a pointer to read
 */
void I2C::testInvalidNullPointerRead()
{
    this->i2c->read(0x31, NULL, 1);
}

/**
 * Ensure that an exception is thrown when a Null pointer for buffer is 
 * passed as a pointer to write
 */
void I2C::testInvalidNullPointerWrite()
{
    this->i2c->write(0x31, NULL, 1);
}

/**
 * Destroy the I2C interface and tear down our tests
 */
void I2C::tearDown()
{
    delete i2c;
}
