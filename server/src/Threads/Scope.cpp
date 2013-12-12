#include <dashee/Threads/Scope.h>

/**
 * Define the pointer to lock
 */ 
dashee::Threads::Scope::Scope(
        dashee::Threads::Lock * lock,
        dashee::Threads::Lock::lockType type
    )
{
    this->lock = lock;
    
    if (lock != NULL)
        this->lock->lock(type);
}

/**
 * Unlock as this class is about to go out of scope
 */
dashee::Threads::Scope::~Scope()
{
    if (this->lock != NULL)
        this->lock->unlock();
}
