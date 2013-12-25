/**
 * @file include/dashee/Coordinate.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */
#ifndef DASHEE_I2C_H_
#define DASHEE_I2C_H_

#include <cstring>
#include <stdlib.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <vector>

#include <dashee/common.h>
#include <dashee/Exception/NullPointer.h>
#include <dashee/Exception/OutOfBounds.h>
#include <dashee/Exception/I2C.h>

namespace dashee
{
    class I2C;
}

/**
 * Wrapper around the I2C interface, which provides read
 * and write register functionality
 */
class dashee::I2C
{

private:
    // Helpful initialize function used by all constructors
    void init(const std::string dev, const unsigned char slaveAddress);

protected:
    /**
     * The file handler to the devices it self
     */
    int fd;

    /**
     * The prefix used when initializing the class with only the int constructor
     */
    static const std::string DEVICE_PREFIX; 

    /**
     * The buffer used to read and write, Its better using a global buffer 
     * rather than initializing one every function call
     */
    char * buffer;

    /**
     * This is the current Slave we are working on, it is used as a store
     * to make the user's life easier
     */
    unsigned char slaveAddress;

public:

    // Open the device using just an integer
    I2C(const int devNumber, const unsigned char slaveAddress = 0x00);
    I2C(const std::string dev, const unsigned char slaveAddress = 0x00);

    // Set the 10 bit address value to true or false, using ioctl
    void set10BitAddress(const bool flag);

    // Set and get the value of the slave
    void setSlaveAddress(const unsigned char slaveAddress);
    unsigned char getSlaveAddress() const;

    // Set and get the working register
    void setWorkingRegister(const unsigned char reg);

    // Read numOfBytes bytes from the register and store it in the buffer
    void read(
	    const unsigned char reg, 
	    std::vector<unsigned char> * const buffer,
	    const size_t numOfBytes
	);

    // Read buffer.size() bytes from the register and store it in the buffer
    void read(
	    const unsigned char reg, 
	    std::vector<unsigned char> * const buffer
	);

    // Write to the register reading the number of bytes from the buffer
    void write(
	    const unsigned char reg,
	    const std::vector<unsigned char> * buffer, 
	    const size_t numOfBytes
	);

    // Write to the register the number of bytes in buffer
    void write(
	    const unsigned char reg,
	    const std::vector<unsigned char> * buffer
	);

    // Clean up
    virtual ~I2C();
};

#endif
