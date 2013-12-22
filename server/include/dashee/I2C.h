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

    /**
     * The working register used to read data, sometime it is faster
     * to just set a register and keep reading from it, to do this we
     * hold the value of our working register in a variable and by setting it
     * we actually write to the device with the value
     */
    unsigned char workingRegister;

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
    void setWorkingRegister(const unsigned char);
    unsigned char getWorkingRegister() const;

    // Read values from the register
    std::vector<unsigned char> readFromRegister(
	    const unsigned char reg, 
	    const size_t numOfBytes
	);
    std::vector<unsigned char> read(const size_t numOfBytes = 1);
    // write values to the register
    //void writeToRegister(const std::vector<unsigned char> buffer);

    // Clean up
    virtual ~I2C();
};

#endif