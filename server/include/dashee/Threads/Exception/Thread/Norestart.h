/**
 * @file include/dashee/Threads/Exception/Thread/Norestart.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_THREADS_EXCEPTION_THREAD_NORESTART_H_
#define DASHEE_THREADS_EXCEPTION_THREAD_NORESTART_H_

#include <dashee/Threads/Exception/Thread.h>

namespace dashee
{
    namespace Threads
    {
        class ExceptionThreadNorestart;
    }
}

class dashee::Threads::ExceptionThreadNorestart : 
    public dashee::Threads::ExceptionThread
{
public:
    explicit ExceptionThreadNorestart() : ExceptionThread()
    {
    }
    explicit ExceptionThreadNorestart(const int ec) : ExceptionThread(ec)
    { 
    }
    explicit ExceptionThreadNorestart(std::string msg) : ExceptionThread(msg)
    { 
    }
};

#endif
