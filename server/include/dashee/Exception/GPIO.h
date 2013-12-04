/**
 * @file include/dashee/Exception/GPIO.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_EXCEPTION_GPIO_H_
#define DASHEE_EXCEPTION_GPIO_H_

#include <dashee/Exception.h>

namespace dashee
{
    class ExceptionGPIO;
}

class dashee::ExceptionGPIO: public dashee::Exception
{
public:
    explicit ExceptionGPIO() : Exception()
    {
    }
    explicit ExceptionGPIO(const int ec) : Exception(ec)
    { 
    }
    explicit ExceptionGPIO(std::string msg) : Exception(msg)
    { 
    }
};

#endif
