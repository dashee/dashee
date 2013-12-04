/**
 * @file include/dashee/Exception/Invalid/Number.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_EXCEPTION_INVALID_NUMBER_H_
#define DASHEE_EXCEPTION_INVALID_NUMBER_H_

#include <dashee/Exception/Invalid.h>

namespace dashee
{
    class ExceptionInvalidNumber;
}

class dashee::ExceptionInvalidNumber : public dashee::ExceptionInvalid
{
public:
    explicit ExceptionInvalidNumber() : ExceptionInvalid()
    {
    }
    explicit ExceptionInvalidNumber(const int ec) : ExceptionInvalid(ec)
    { 
    }
    explicit ExceptionInvalidNumber(std::string msg) : ExceptionInvalid(msg)
    { 
    }
};

#endif
