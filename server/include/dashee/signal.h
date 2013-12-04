/**
 * @file include/dashee/daemon.h
 * @author Shahmir Javaid
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license.  
 */

#ifndef DASHEE_SIGNAL_H_
#define DASHEE_SIGNAL_H_

#include <signal.h>
#include <dashee/Log.h>

namespace dashee
{
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
    void handleTerminateSignal(int sig);
    void handleReloadSignal(int sig);

    // initialize our Signal handlers
    void initSignalHandler();
}

#endif
