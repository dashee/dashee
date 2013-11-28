#include <dashee/Mutex.h>

/**
 * Contruct our Mutex
 */
dashee::Mutex::Mutex()
{
    this->mutex = new pthread_mutex_t();
    this->attr = NULL;
    
    // Make sure that initilization comes out as good, otherwise we should
    // absolutly die die die
    int ec = pthread_mutex_init(this->mutex, this->attr);
    if (ec != 0)
	throw ExceptionMutex(
		"Error Initilizing Mutex, ec='" + 
		dashee::itostr(ec) + "'. This should not happen!"
	    );
}

/**
 * Lock our mutex.
 *
 * @throws ExceptionMutex If exit code is not 0
 */
void dashee::Mutex::lock()
{
    int ec = pthread_mutex_lock(this->mutex);

    switch (ec)
    {
	case 0:
	    return;
	    break;
	case EINVAL:
	    throw ExceptionMutex(
		    "EINVAL thrown when locking, see man page for details."
		);
	    break;
	case EAGAIN:
	    throw ExceptionMutex("Max number of Mutex locks reached.");
	    break;
	case EDEADLK:
	    throw ExceptionMutex(
		    "Cannot double lock the same mutex in one thread."
		);
	    break;
	default:
            throw ExceptionMutex(
                    "Unknown error in Mutex::lock, ec='" + 
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
 *
 * @return TRUE if locked, FALSE if failed to lock given contraints
 */
bool dashee::Mutex::trylock(int ntimes, int npause)
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
		throw ExceptionMutex(
			"EINVAL thrown when trying lock, see man page for "
			"details."
		    );
		break;
	    case EAGAIN:
		throw ExceptionMutex("Max number of Mutex locks reached.");
		break;
	    default:
		throw ExceptionMutex(
			"Unknown error in Mutex::trylock, ec='" + 
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
 * @throws ExceptionMutex If exit code is not 0
 */
void dashee::Mutex::unlock()
{
    int ec = pthread_mutex_unlock(this->mutex);

    switch (ec)
    {
	case 0:
	    return;
	    break;
	case EINVAL:
	    throw ExceptionMutex(
		    "EINVAL thrown when locking, see man page for details."
		);
	    break;
	case EAGAIN:
	    throw ExceptionMutex("Max number of Mutex locks reached.");
	    break;
	case EPERM:
	    throw ExceptionMutex(
		    "Cannot unlock neighbours mutex, Mutex must be owned by "
		    "this thread by using Mutex::lock before Mutex::unlock can "
		    "be called"
		);
	    break;
	default:
            throw ExceptionMutex(
                    "Unknown error in Mutex::unlock, ec='" + 
		    dashee::itostr(ec) + "'. This should not happen!"
                );
            break;
	
    }	
}

/**
 * Delete our mutex
 */
dashee::Mutex::~Mutex()
{
    pthread_mutex_destroy(this->mutex);
    delete this->mutex;
}   
