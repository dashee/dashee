/** 
 * @file src/servod/threads.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 *
 * @section DESCRIPTION 
 *
 * The threads used in our servod program are defined here. The definition of 
 * main variables is defined in the servod.cpp. And this file is included post
 * definition so it can use those variables.
 */

#ifndef DASHEE_SERVOD_THREADS_H_
#define DASHEE_SERVOD_THREADS_H_

#include <queue>

#include <dashee/Threads/Thread.h>
#include <dashee/Threads/Scope.h>
#include <dashee/Threads/Lock.h>
#include <dashee/Threads/Lock/Mutex.h>
#include <dashee/Threads/Lock/ReadWrite.h>
#include <dashee/Server.h>
#include <dashee/Vehicle.h>

#include "signals.h"
#include "Container.h"
#include "Controller.h"

extern dashee::Threads::LockReadWrite lockSensor;
extern dashee::Threads::LockReadWrite lockConfig;
extern dashee::Threads::LockReadWrite lockSever;
extern dashee::Threads::LockReadWrite lockServoController;
extern dashee::Threads::LockReadWrite lockVehicle;
extern dashee::Threads::LockMutex lockBuffer;
extern dashee::Threads::LockReadWrite lockEXIT;
extern dashee::Threads::LockReadWrite lockRELOAD;

/**
 * Buffer which is passed from the server to the
 * controller
 */
extern std::queue<unsigned char> buffer;

// Thread to wait for a data, and update the controller
void threadInitilizeContainer(Container * c);

// Thread to wait for a data, and update the controller
void * threadReadFromServer(void *);

// Thread to poll the sensor and update the model
void * threadUpdateSensors(void *);

// Thread to loop through the controller
void * threadStepController(void * c);

#endif
