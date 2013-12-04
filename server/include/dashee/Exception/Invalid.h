/**
 * @file include/dashee/Exception/Invalid.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_EXCEPTION_INVALID_H_
#define DASHEE_EXCEPTION_INVALID_H_

#include <dashee/Exception.h>

namespace dashee
{
    class ExceptionInvalid;
}

class dashee::ExceptionInvalid : public dashee::Exception
{
public:
    explicit ExceptionInvalid() : Exception()
    {
    }
    explicit ExceptionInvalid(const int ec) : Exception(ec)
    { 
    }
    explicit ExceptionInvalid(std::string msg) : Exception(msg)
    { 
    }
};

#endif
