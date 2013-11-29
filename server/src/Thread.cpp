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

    int ec = pthread_create(
                this->thread, 
                NULL, 
                thread_entry_function, 
                (parameter_to_entry_function)
            );

    // Handle the return value of the function
    switch (ec)
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
                    "Unknown error in Thread::start ec='" + 
                    dashee::itostr(ec) + "'. This should not happen!"
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
 * Calls a pthread_self
 *
 * @returns threadid
 */
pthread_t dashee::Thread::self()
{
    return pthread_self();
}

/**
 * Exit the current thread, by calling pthread_exit;
 *
 * @param retval Pass a parameter through to join
 */
void dashee::Thread::exit(int retval)
{
    pthread_exit(&retval);
}

/**
 * Destroy new variables
 */
dashee::Thread::~Thread()
{
    delete this->thread;
}
