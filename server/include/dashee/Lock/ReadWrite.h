/**
 * @file include/dashee/Lock/ReadWrite.h
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

#ifndef DASHEE_LOCK_READWRITE_H_
#define DASHEE_LOCK_READWRITE_H_

#include <dashee/Lock.h>

namespace dashee
{
    class LockReadWrite;
}

/**
 * Lock Read only.
 *
 * Class that implements the read lock
 */ 
class dashee::LockReadWrite : public dashee::Lock
{
public:
    /**
     * Enumurator which represents the type of locks
     */
    enum lockType { LOCKTYPE_READ, LOCKTYPE_WRITE };



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
    LockReadWrite(lockType type = LOCKTYPE_READ);

    void setLockType(lockType type);
    
    void lock();
    void unlock();

    // If you are feeling board, do implement
    bool trylock(int ntimes = 0, int npause = 0);
    
    // Destruct the thread
    ~LockReadWrite();
};

#endif
