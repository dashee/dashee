/**
 * @file include/dashee/Exception/Config.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_EXCEPTION_CONFIG_H_
#define DASHEE_EXCEPTION_CONFIG_H_

#include <dashee/Exception.h>

namespace dashee
{
    class ExceptionConfig;
}

class dashee::ExceptionConfig: public dashee::Exception
{
public:
    explicit ExceptionConfig() : Exception()
    {
    }
    explicit ExceptionConfig(const int ec) : Exception(ec)
    { 
    }
    explicit ExceptionConfig(std::string msg) : Exception(msg)
    { 
    }
};

#endif
