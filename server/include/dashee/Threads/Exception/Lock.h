/**
 * @file include/dashee/Threads/Exception/Lock.h
 * @author Shahmir Javaid
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_THREADS_EXCEPTION_LOCK_H_
#define DASHEE_THREADS_EXCEPTION_LOCK_H_

#include <dashee/Threads/Exception.h>

namespace dashee
{
    namespace Threads
    {
        class ExceptionLock;
    }
}

class dashee::Threads::ExceptionLock: public dashee::Threads::Exception
{
public:
    explicit ExceptionLock() : Exception()
    {
    }
    explicit ExceptionLock(const int ec) : Exception(ec)
    { 
    }
    explicit ExceptionLock(std::string msg) : Exception(msg)
    { 
    }
};

#endif

