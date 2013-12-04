/**
 * @file include/dashee/Exception/OutOfBounds.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_EXCEPTION_OUTOFBOUNDS_H_
#define DASHEE_EXCEPTION_OUTOFBOUNDS_H_

#include <dashee/Exception.h>

namespace dashee
{
    class ExceptionOutOfBounds;
}

class dashee::ExceptionOutOfBounds: public dashee::Exception
{
public:
    explicit ExceptionOutOfBounds() : Exception()
    {
    }
    explicit ExceptionOutOfBounds(const int ec) : Exception(ec)
    { 
    }
    explicit ExceptionOutOfBounds(std::string msg) : Exception(msg)
    { 
    }
};

#endif
