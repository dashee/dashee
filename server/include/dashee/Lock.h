/**
 * @file include/dashee/Lock.h
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

#ifndef DASHEE_LOCK_H_
#define DASHEE_LOCK_H_

#include <pthread.h>
#include <dashee/common.h>
#include <dashee/Exception/Lock.h>

namespace dashee
{
    class Lock;
}

/**
 * Interface for Locking objects
 */ 
class dashee::Lock
{
public:
    virtual void lock() = 0;
    virtual void unlock() = 0;
    virtual bool trylock(int ntimes = 0, int npause = 0) = 0;
};

#endif

