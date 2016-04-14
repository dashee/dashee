/**
 * @file include/dashee/Exception/NullPointer.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_EXCEPTION_NULLPOINTER_H_
#define DASHEE_EXCEPTION_NULLPOINTER_H_

#include <dashee/Exception.h>

namespace dashee
{
    class ExceptionNullPointer;
}

class dashee::ExceptionNullPointer: public dashee::Exception
{
public:
    explicit ExceptionNullPointer() : Exception()
    {
    }
    explicit ExceptionNullPointer(const int ec) : Exception(ec)
    { 
    }
    explicit ExceptionNullPointer(std::string msg) : Exception(msg)
    { 
    }
};

#endif
