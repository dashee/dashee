/**
 * @file include/dashee/Threads/Exception/Thread/Notathread.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_THREADS_EXCEPTION_THREAD_NOTATHREAD_H_
#define DASHEE_THREADS_EXCEPTION_THREAD_NOTATHREAD_H_

#include <dashee/Threads/Exception/Thread.h>

namespace dashee
{
    namespace Threads
    {
        class ExceptionThreadNotathread;
    }
}

class dashee::Threads::ExceptionThreadNotathread : 
    public dashee::Threads::ExceptionThread
{
public:
    explicit ExceptionThreadNotathread() : ExceptionThread()
    {
    }
    explicit ExceptionThreadNotathread(const int ec) : ExceptionThread(ec)
    { 
    }
    explicit ExceptionThreadNotathread(std::string msg) : ExceptionThread(msg)
    { 
    }
};

#endif
