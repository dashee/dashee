/**
 * @file include/dashee/Hardware/Exception.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_HARDWARE_EXCEPTION_H_
#define DASHEE_HARDWARE_EXCEPTION_H_

#include <dashee/Exception.h>

namespace dashee
{
    namespace Hardware
    {
        class Exception;
    }
}

class dashee::Hardware::Exception: public dashee::Exception
{
public:
    explicit Exception() : dashee::Exception()
    {
    }
    explicit Exception(const int ec) : dashee::Exception(ec)
    { 
    }
    explicit Exception(std::string msg) : dashee::Exception(msg)
    { 
    }
};

#endif
