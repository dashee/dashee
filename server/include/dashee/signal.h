/**
 * @file include/dashee/daemon.h
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
 *                     you may distribute the resulting work only under a licence 
 *                     identical to this one.
 *
 * The terms and conditions are updated at http://dashee.co.uk/license. View the
 * project site for more details
 */

#ifndef DASHEE_SIGNAL_H_
#define DASHEE_SIGNAL_H_

#include <signal.h>

#include <dashee/Log.h>

namespace dashee
{
    /**
     * This is our main variable that controls wheather or not the program should be running
     * As soon as this variable is set to 1, all threads should start exiting gracefully, 
     * and pselect() would have by this time timed out
     */
    int volatile EXIT = 0;

    /**
     * This is set to 0, but SIGUP will set it to 1, This will cause the system
     * to reload options from configurations and reset our running objects
     */
    int volatile RELOAD = 0;

    // Signal handlers
    void handleTerminateSignal(int sig);
    void handleReloadSignal(int sig);

    // initialize our Signal handlers
    void initSignalHandler();

}

#endif
