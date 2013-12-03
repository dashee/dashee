/** 
 * @file src/servod/loads.h
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
 */

#ifndef DASHEE_SERVOD_LOADS_H_
#define DASHEE_SERVOD_LOADS_H_

#include <getopt.h> /* for getopts_long() */

#include <dashee/Log.h>
#include <dashee/Config.h>
#include <dashee/ServoController/UART.h>
#include <dashee/ServoController/USB.h>
#include <dashee/ServoController/Dummy.h>
#include <dashee/Server/UDP.h>
#include <dashee/Vehicle/Car.h>
#include <dashee/Vehicle/Multirotor/Quad/X.h>
#include <dashee/signal.h>

#define DASHEE_PIDFILE "./var/run/dashee/servod.pid"
#define DASHEE_LOGFILE "./var/log/dashee/servod.log"
#define DASHEE_WORKINGDIR "."
#define DASHEE_CONFIG "./etc/dashee/servod.conf"

#define SERVOD_DEVICE "/dev/ttyAMA0"
#define SERVOD_DEVICETYPE 1
#define SERVOD_CHANNELS 6

#define VEHICLE_TYPE "Car"

#define DASHEE_SERVER_PORT 2047u
#define DASHEE_SERVER_TIMEOUT 2u

// Load our objects
dashee::Config * loadConfig(int argc, char ** argv);
dashee::ServoController * loadServoController(dashee::Config * config);
dashee::Server * loadServer(dashee::Config * config);
dashee::Vehicle * loadVehicle(
        dashee::Config * config,
        dashee::ServoController * servoController
    );

// Reload Objects given we have recieved a signal
void reloadSystem(
        int argc,
        char ** argv,
        dashee::ServoController * servoController,
        dashee::Server * server,
        dashee::Vehicle * vehicle
    );

#endif
