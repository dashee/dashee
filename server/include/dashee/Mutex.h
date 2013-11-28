/**
 * @file include/dashee/Mutex.h
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

#ifndef DASHEE_MUTEX_H_
#define DASHEE_MUTEX_H_

#include <pthread.h>
#include <dashee/Exception/Mutex.h>
#include <dashee/common.h>

namespace dashee
{
    class Mutex;
}

/**
 * Mutex class.
 *
 * This class is designed to create locks and release locks on mutex variables.
 * This mainly encapsulates the pthread_mutex_ API calls
 */ 
class dashee::Mutex
{
private:

    /**
     * The mutex handler.
     */
    pthread_mutex_t * mutex;

    /**
     * The mutex attributes
     */
    pthread_mutexattr_t * attr;


public:

    // New instance of the thread
    Mutex();
    
    void lock();
    void unlock();

    // If you are feeling board, do implement
    bool trylock(int ntimes = 0, int npause = 0);
    
    // Destruct the thread
    ~Mutex();
};

#endif

