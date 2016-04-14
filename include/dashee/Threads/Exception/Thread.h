/**
 * @file include/dashee/Threads/Exception/Thread.h
 * @author Shahmir Javaid
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_THREADS_EXCEPTION_THREAD_H_
#define DASHEE_THREADS_EXCEPTION_THREAD_H_

#include <dashee/Threads/Exception.h>

namespace dashee
{
    namespace Threads
    {
        class ExceptionThread;
    }
}

class dashee::Threads::ExceptionThread: public dashee::Threads::Exception
{
public:
    explicit ExceptionThread() : Exception()
    {
    }
    explicit ExceptionThread(const int ec) : Exception(ec)
    { 
    }
    explicit ExceptionThread(std::string msg) : Exception(msg)
    { 
    }
};

#endif
