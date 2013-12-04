/**
 * @file include/dashee/Threads/Lock.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_THREADS_LOCK_H_
#define DASHEE_THREADS_LOCK_H_

#include <pthread.h>
#include <dashee/common.h>
#include <dashee/Threads/Exception/Lock/Deadlock.h>

namespace dashee
{
    namespace Threads
    {
        class Lock;
    }
}

/**
 * Interface for Locking objects
 */ 
class dashee::Threads::Lock
{
public:

    /**
     * Enumurator which represents the type of locks
     */
    enum lockType { LOCKTYPE_READ, LOCKTYPE_WRITE };

    virtual void lock(lockType type = LOCKTYPE_WRITE) = 0;
    virtual void unlock() = 0;
    virtual bool trylock(
	    int ntimes = 0, 
	    int npause = 0,
	    lockType type = LOCKTYPE_WRITE
	) = 0;
};

#endif

