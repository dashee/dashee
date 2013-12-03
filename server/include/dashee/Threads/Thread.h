/**
 * @file include/dashee/Threads/Thread.h
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

#ifndef DASHEE_THREADS_THREAD_H_
#define DASHEE_THREADS_THREAD_H_

#include <pthread.h>

#include <dashee/common.h>
#include <dashee/Threads/Exception/Thread.h>
#include <dashee/Threads/Exception/Thread/Norestart.h>
#include <dashee/Threads/Exception/Thread/Notathread.h>

namespace dashee
{
    namespace Threads
    {
        class Thread;
    }
}

/**
 * The Thread class.
 *
 * This class encapsulates the thread functionality used by our system, It 
 * mainly encapsulates pthread_t API, but later could be used for other types.
 *
 * Main responsiblities include, starting a thread, and joining it.
 */ 
class dashee::Threads::Thread
{
private:

    /**
     * The pointer to the entry point function.
     */
    void * (*thread_entry_function)(void *);

    /**
     * The instance of the thread that this
     * current object represents
     */
    pthread_t * thread;

    /**
     * Boolean which holds start flag, we dont want to call pthread_create 
     * mutiple times for the same object
     */
    bool started;

public:

    // New instance of the thread
    Thread(void * (*thread_entry_function)(void *));

    // Start the thread, one time operation only
    void start(void * parameter_to_entry_function);

    // Joining the thread
    void * join();

    static pthread_t self();

    // Call exit on a thread, usefull for external calls
    static void exit(void * retval = NULL);

    // Destruct the thread
    ~Thread();
};

#endif
