/**
 * @file include/dashee/Threads/Exception/Thread/Notathread.h
 * @author Shahmir Javaid
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. In general
 * you are free to copy, distribute, display, and perform the work, 
 * you are also free to make derivative works, under the following conditions:
 *  - Attribution    — You must give dashee's author credit.
 *  - Non-Commercial - You may not use this dashee for commercial 
 *                     purposes without permission.
 *  - Share Alike    — If you alter, transform, or build upon this work, 
 *                     you may distribute the resulting work only under a 
 *                     licence identical to this one.
 *
 * The terms and conditions are updated at http://dashee.co.uk/license. View the
 * project site for more details
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
