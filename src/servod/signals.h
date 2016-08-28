/**
 * @file src/servod/signals.h
 * @author Shahmir Javaid
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license.  
 */

#ifndef DASHEE_SERVOD_SIGNALS_H_
#define DASHEE_SERVOD_SIGNALS_H_

#include "threads.h"
#include <dashee/Log.h>
#include <vector>

extern std::vector<dashee::Threads::Thread *> signalThreads;

/**
 * This is our main variable that controls wheather or not the program 
 * should be running. As soon as this variable is set to 1, all threads 
 * should start exiting gracefully, and pselect() would have by this time 
 * timed out
 */
extern int volatile EXIT;

/**
 * This is set to 0, but SIGUP will set it to 1, This will cause the system
 * to reload options from configurations and reset our running objects
 */
extern int volatile RELOAD;

// Signal handlers
void signalTerminateHandler(int sig);
void signalReloadHandler(int sig);
void signalNothingHandler(int sig);

// Loop through signalThreads and call signal
void signalAllThreads(int sig);

// initialize our Signal handlers
void initSignal();

#endif
