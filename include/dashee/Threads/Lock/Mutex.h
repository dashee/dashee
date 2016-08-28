/**
 * @file include/dashee/Threads/Lock/Mutex.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_THREADS_LOCK_MUTEX_H_
#define DASHEE_THREADS_LOCK_MUTEX_H_

#include <dashee/Threads/Lock.h>

namespace dashee
{
    namespace Threads
    {
        class LockMutex;
    }
}

/**
 * Mutex class.
 *
 * This class is designed to create locks and release locks on mutex variables.
 * This mainly encapsulates the pthread_mutex_ API calls
 */ 
class dashee::Threads::LockMutex : public dashee::Threads::Lock
{
private:

    /**
     * The mutex handler.
     */
    pthread_mutex_t * mutex;

    /**
     * The mutex attributes
     */
    pthread_mutexattr_t * attr;

public:

    // New instance of the thread
    LockMutex();
    
    void lock(lockType type = LOCKTYPE_WRITE);
    void unlock();

    // If you are feeling board, do implement
    bool trylock(
	    int ntimes = 0,
	    int npause = 0,
	    lockType type = LOCKTYPE_WRITE
	);
    
    // Destruct the thread
    ~LockMutex();
};

#endif

