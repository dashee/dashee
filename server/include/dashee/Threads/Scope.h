/**
 * @file include/dashee/Threads/Scope.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_THREADS_SCOPE_H_
#define DASHEE_THREADS_SCOPE_H_

#include <dashee/Threads/Lock.h>

namespace dashee
{
    namespace Threads
    {
        class Scope;
    }
}

/**
 * Unlock a mutex
 *
 * Implementing RAII (Resource Acquisition Is Initialisation) concept. See 
 * http://stackoverflow.com/questions/14276508/how-does-scope-locking-work
 */
class dashee::Threads::Scope
{
private:
    Lock * lock;

public:

    // Lock
    Scope(Lock * lock, Lock::lockType = Lock::LOCKTYPE_WRITE);

    // Unlock
    ~Scope();
};

#endif
