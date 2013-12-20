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
#include <fcntl.h>

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
    void init(const std::string dev);

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

public:

    // Open the device using just an integer
    I2C(const int devNumber);
    I2C(const std::string dev);

    // Clean up
    virtual ~I2C();
};

#endif
