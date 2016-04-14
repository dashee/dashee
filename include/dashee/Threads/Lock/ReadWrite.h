/**
 * @file include/dashee/Threads/Lock/ReadWrite.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_THREADS_LOCK_READWRITE_H_
#define DASHEE_THREADS_LOCK_READWRITE_H_

#include <dashee/Threads/Lock.h>

namespace dashee
{
    namespace Threads
    {
        class LockReadWrite;
    }
}

/**
 * Lock Read only.
 *
 * Class that implements the read lock
 */ 
class dashee::Threads::LockReadWrite : public dashee::Threads::Lock
{
public:

private:

    /**
     * The rwlock handler.
     */
    pthread_rwlock_t * rwlock;

    /**
     * The rwlock attributes
     */
    pthread_rwlockattr_t * attr;

    /**
     * The type of lock to set
     */
    lockType type;

public:

    // New instance of the thread
    LockReadWrite();
    
    void lock(lockType type = LOCKTYPE_WRITE);
    void unlock();

    // If you are feeling board, do implement
    bool trylock(
	    int ntimes = 0, 
	    int npause = 0,
	    lockType type = LOCKTYPE_WRITE
	);
    
    // Destruct the thread
    ~LockReadWrite();
};

#endif
