/** 
 * @file src/servod/threads.h
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
 *
 * @section DESCRIPTION 
 *
 * The threads used in our servod program are defined here. The definition of 
 * main variables is defined in the servod.cpp. And this file is included post
 * definition so it can use those variables.
 */

#ifndef DASHEE_SERVOD_THREADS_H_
#define DASHEE_SERVOD_THREADS_H_

#include <dashee/Threads/Thread.h>
#include <dashee/Threads/Lock.h>
#include <dashee/Threads/Lock/Mutex.h>
#include <dashee/Threads/Lock/ReadWrite.h>
#include <dashee/signal.h>

/**
 * Lock our sensor when reading.
 */
dashee::Threads::LockReadWrite lockReadSensor 
    = dashee::Threads::LockReadWrite();

/**
 * Lock our sensor when writing.
 */
dashee::Threads::LockReadWrite lockWriteSensor 
    = dashee::Threads::LockReadWrite(
            dashee::Threads::LockReadWrite::LOCKTYPE_WRITE
        );

/**
 * Lock our vehicle for updating
 */
dashee::Threads::LockReadWrite lockWriteVehicle 
    = dashee::Threads::LockReadWrite(
            dashee::Threads::LockReadWrite::LOCKTYPE_WRITE
        );

// Thread to wait for a data, and update the controller
void * threadReadFromServer(void *);

// Thread to poll the sensor and update the model
void * threadUpdateSensors(void *);

// Thread to loop through the controller
void * threadStepController(void *);

#endif
