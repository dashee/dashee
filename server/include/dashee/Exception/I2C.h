/**
 * @file include/dashee/Exception/I2C.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_EXCEPTION_I2C_H_
#define DASHEE_EXCEPTION_I2C_H_

#include <dashee/Exception.h>

namespace dashee
{
    class ExceptionI2C;
}

class dashee::ExceptionI2C: public dashee::Exception
{
public:
    explicit ExceptionI2C() : Exception()
    {
    }
    explicit ExceptionI2C(const int ec) : Exception(ec)
    { 
    }
    explicit ExceptionI2C(std::string msg) : Exception(msg)
    { 
    }
};

#endif

