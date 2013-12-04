/**
 * @file include/dashee/Exception/Invalid/Value.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_EXCEPTION_INVALID_VALUE_H_
#define DASHEE_EXCEPTION_INVALID_VALUE_H_

#include <dashee/Exception.h>

namespace dashee
{
    class ExceptionInvalidValue;
}

class dashee::ExceptionInvalidValue : public dashee::ExceptionInvalid
{
public:
    explicit ExceptionInvalidValue() : ExceptionInvalid()
    {
    }
    explicit ExceptionInvalidValue(const int ec) : ExceptionInvalid(ec)
    { 
    }
    explicit ExceptionInvalidValue(std::string msg) : ExceptionInvalid(msg)
    { 
    }
};

#endif
