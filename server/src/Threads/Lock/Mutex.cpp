#include <dashee/Threads/Lock/Mutex.h>

/**
 * Contruct our Mutex
 */
dashee::Threads::LockMutex::LockMutex()
{
    this->mutex = new pthread_mutex_t();
    this->attr = new pthread_mutexattr_t();
    
    if (pthread_mutexattr_init(this->attr) != 0)
	throw ExceptionLock("Thread attribute init failed");

    if (pthread_mutexattr_settype(this->attr, PTHREAD_MUTEX_ERRORCHECK) != 0)
	throw ExceptionLock("Thread attribute set failed");
    
    // Make sure that initilization comes out as good, otherwise we should
    // absolutly die die die
    int ec = pthread_mutex_init(this->mutex, this->attr);
    if (ec != 0)
	throw ExceptionLock(
		"Error Initilizing LockMutex, ec='" + 
		dashee::itostr(ec) + "'. This should not happen!"
	    );

    pthread_mutexattr_destroy(this->attr);
    this->attr = NULL;
}

/**
 * Lock our mutex.
 *
 * @param type Read or Write?
 *
 * @throws ExceptionLock If exit code is not 0
 */
void dashee::Threads::LockMutex::lock(lockType type)
{
    int ec = pthread_mutex_lock(this->mutex);

    switch (ec)
    {
	case 0:
	    return;
	    break;
	case EINVAL:
	    throw ExceptionLock(
		    "EINVAL thrown when locking, see man page for details."
		);
	    break;
	case EAGAIN:
	    throw ExceptionLock("Max number of Mutex locks reached.");
	    break;
	case EDEADLK:
	    throw ExceptionLockDeadlock(
		    "Cannot double lock the same mutex in one thread."
		);
	    break;
	default:
            throw ExceptionLock(
                    "Unknown error in LockMutex::lock, ec='" + 
		    dashee::itostr(ec) + "'. This should not happen!"
                );
            break;
	
    }	
}

/**
 * Try lock ntimes. If ntimes is set to 0 then try lock forever
 *
 * @param ntimes The number of times to try locking, 0 is unlimited
 * @param npause The number of seconds to sleep in the case of failed try
 * @param type Read or Write?
 *
 * @return TRUE if locked, FALSE if failed to lock given contraints
 */
bool dashee::Threads::LockMutex::trylock(int ntimes, int npause, lockType type)
{
    int n = 0;
    int ec;
    while ((ec = pthread_mutex_trylock(this->mutex)) != 0)
    {
	// Lock is busy, add to ntimes if > 0 and increment the counter
	// When adding sleep for npause time
	if (ec == EBUSY)
	{
	    dashee::sleep(npause);

	    // If ntimes is not 0 that means only try lock n times
	    if (ntimes != 0)
	    {
		if (n <= ntimes)
		    return false;

		n++;
	    }
		
	    continue;
	}

	// Handle errors
	switch (ec)
	{
	    case EINVAL:
		throw ExceptionLock(
			"EINVAL thrown when trying lock, see man page for "
			"details."
		    );
		break;
	    case EAGAIN:
		throw ExceptionLock("Max number of Mutex locks reached.");
		break;
	    default:
		throw ExceptionLock(
			"Unknown error in LockMutex::trylock, ec='" + 
			dashee::itostr(ec) + "'. This should not happen!"
		    );
		break;
	}	
    }	

    return true;
}

/**
 * Unlock our mutex.
 *
 * @throws ExceptionLock If exit code is not 0
 */
void dashee::Threads::LockMutex::unlock()
{
    int ec = pthread_mutex_unlock(this->mutex);

    switch (ec)
    {
	case 0:
	    return;
	    break;
	case EINVAL:
	    throw ExceptionLock(
		    "EINVAL thrown when locking, see man page for details."
		);
	    break;
	case EAGAIN:
	    throw ExceptionLock("Max number of Mutex locks reached.");
	    break;
	case EPERM:
	    throw ExceptionLock(
		    "Cannot unlock neighbours mutex, Mutex must be owned by "
		    "this thread by using Mutex::lock before Mutex::unlock can "
		    "be called"
		);
	    break;
	default:
            throw ExceptionLock(
                    "Unknown error in LockMutex::unlock, ec='" + 
		    dashee::itostr(ec) + "'. This should not happen!"
                );
            break;
	
    }	
}

/**
 * Delete our mutex
 */
dashee::Threads::LockMutex::~LockMutex()
{
    pthread_mutex_destroy(this->mutex);
    delete this->mutex;
}   
