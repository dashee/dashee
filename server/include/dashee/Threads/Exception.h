/**
 * @file include/dashee/Threads/Exception.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_THREADS_EXCEPTION_H_
#define DASHEE_THREADS_EXCEPTION_H_

#include <dashee/Exception.h>

namespace dashee
{
    namespace Threads
    {
        class Exception;
    }
}

class dashee::Threads::Exception: public dashee::Exception
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
