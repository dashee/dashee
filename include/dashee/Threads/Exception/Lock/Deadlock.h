/**
 * @file include/dashee/Threads/Exception/Lock/Deadlock.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_THREADS_EXCEPTION_LOCK_DEADLOCK_H_
#define DASHEE_THREADS_EXCEPTION_LOCK_DEADLOCK_H_

#include <dashee/Threads/Exception/Lock.h>

namespace dashee
{
    namespace Threads
    {
        class ExceptionLockDeadlock;
    }
}

class dashee::Threads::ExceptionLockDeadlock 
    : public dashee::Threads::ExceptionLock
{
public:
    explicit ExceptionLockDeadlock() : ExceptionLock()
    {
    }
    explicit ExceptionLockDeadlock(const int ec) : ExceptionLock(ec)
    { 
    }
    explicit ExceptionLockDeadlock(std::string msg) : ExceptionLock(msg)
    { 
    }
};

#endif

