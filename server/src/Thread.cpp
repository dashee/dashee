#include <dashee/Thread.h>

/**
 * Construct our thread, and initilize our variables
 *
 * @param thread_entry_function The function to perform magic on
 */
dashee::Thread::Thread(void * (*thread_entry_function)(void *))
{
    this->thread_entry_function = thread_entry_function;
    this->thread = new pthread_t();
    this->started = false;
}

/**
 * Start our thread.
 *
 * Ensure that our thread is not already running before starting. Also handle
 * the pthread_create error gracefully by converting them into exceptions.
 *
 * If the thread is successfully created, turn the started flag to true and 
 * return without any thrown exceptions
 *
 * @param parameter_to_entry_function the pointer to the object that the entry
 *  function uses to perform its actions
 *
 * @throws ExceptionThreadNorestart When the thread has already been started, 
 *  it must be killed by calling exit() before it can be called again
 * @throws ExceptionThread When pthread_create fails
 */
void dashee::Thread::start(void * parameter_to_entry_function)
{
    // Ensure it is not already running
    if (this->started)
        throw ExceptionThreadNorestart(
                "Thread must be killed before restarting, "
                "try Thread::exit() and Thread::start(void *)"
            );

    int retval = pthread_create(
                this->thread, 
                NULL, 
                thread_entry_function, 
                (parameter_to_entry_function)
            );

    // Insert into the pool, It will update this every time, if it already
    pool.insert(Threads::pair(*(this->thread), this));

    // Handle the return value of the function
    switch (retval)
    {
        // All is well
        case 0:
            this->started = true;
            break;

        // Errors see `man pthread_create`
        case EAGAIN:
            throw ExceptionThread(
                    "Insufficient  resources  to create another thread, "
                    "or a system-imposed limit on the number of threads "
                    "was encountered."
                );
            break;
        case EINVAL:
            throw ExceptionThread("Invalid attribute to pthread_create.");
            break;
        case EPERM:
            throw ExceptionThread(
                    "No permission to set the scheduling policy "
                    "and parameters specified in attr."
                );
            break;

        // This should not happen
        default:
            throw ExceptionThread(
                    "Unknown error in Thread::start post pthread_create, "
                    "This should not happen!"
                );
            break;
    }
}

/**
 * Caller to wait for the thread to finish.
 *
 * For more see pthread_join
 *
 * @returns int value of pthread_join return
 *
 * @throws ExceptionThread If a non 0 pthread value was returned
 */
void dashee::Thread::join()
{
    if (!this->started)
        throw ExceptionThread("Cannot join a stoped thread.");

    int ec = pthread_join(*(this->thread), NULL);
            
    this->started = false;

    // Handle the return value of the function
    switch (ec)
    {
        // All is well, do some cleanup
        case 0:
            return;
            break;

        // Errors see `man pthread_create`
        case EDEADLK:
            throw ExceptionThread("Deadlock was detected");
            break;
        case EINVAL:
            throw ExceptionThread("Thread is not a joinable thread.");
            break;
        case EPERM:
            throw ExceptionThread("Another thread is already waiting to join");
            break;

        // This should not happen
        default:
            throw ExceptionThread(
                    "Exit code came back with '" + dashee::itostr(ec) + "'."
                );
            break;
    }
}

/**
 * This is a handy function which calls pthread_self, and looks in the running
 * map to return the Thread pointer to the object this thread id belongs to.
 *
 * @returns Thread pointer to the object, or NULL if not found
 */
dashee::Thread * dashee::Thread::self()
{
    Threads::map::iterator it = pool.find(pthread_self());

    if (it == pool.end())
        return NULL;

    return it->second;
}

/**
 * Exit our running thread. But make sure the call is ran inside
 * its own called thread. you cannot call exit on a thread from another process
 *
 * @param retval Pass a parameter through to join
 *
 * @throws ExceptionThreadNotathread If called on a non thread, should not be 
 *  allowed
 */
void dashee::Thread::exit(int retval)
{
    if (Thread::self() == NULL)
        throw ExceptionThreadNotathread(
                "You cannot call exit on an unknown thread"
            );

    pthread_exit(&retval);
}

/**
 * Returns the size of the pool
 *
 * @returns The size of the current pool
 */
size_t dashee::Thread::size()
{
    return pool.size();
}   

/**
 * Destruct our object cleanly, first remove it from the pool of threads
 * which is heald internally in a map variable, second delete the thread
 * variable
 */
dashee::Thread::~Thread()
{
    // If it was never started, the value here should be 0
    if (this->thread != NULL)
        pool.erase(*(this->thread));

    delete this->thread;
}

// Initilize our pool, Dont really need this but good practice
dashee::Threads::map dashee::Thread::pool 
    = dashee::Threads::map();
