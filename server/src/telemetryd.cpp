/** 
 * @file src/servod.cpp
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
 *
 * @section DESCRIPTION 
 *
 * This program is designed to read the computers current status
 * and return it through a TCP/IP protocol. It returns:
 *   Uptime TODO
 *   System Time TODO
 *   CPU Usage TODO
 *   Memory Usage TODO
 *   Disk Space TODO
 *   IP Addresses TODO
 *   GPS TODO
 *   Gyro TODO
 *   Accellerometer TODO
 *   Magnometer TODO
 *   Barometer TODO
 *   Airspeed TODO
 *   Voltage TODO
 */

#include <stdlib.h>
#include <sstream>
#include <getopt.h> /* for getopts_long() */
#include <dashee/common.h>
#include <dashee/Log.h>
#include <dashee/Config.h>
#include <dashee/Server/UDP.h>
//#include "Config.h"

#define TELEMETRYD_PORT 2047u
#define TELEMETRYD_TIMEOUT 2u
#define TELEMETRYD_LOGFILE "./var/log/dashee/telemetryd.log"
#define TELEMETRYD_CONFIG "./etc/dashee/telemetryd.conf"
#define TELEMETRYD_PIDFILE "./var/run/dashee/telemetryd.pid"
#define TELEMETRYD_WORKINGDIR "."

/**
 * This is our main variable that controls wheather or not the program should be running
 * As soon as this variable is set to 1, all threads should start exiting gracefully, 
 * and pselect() would have by this time timed out
 */
int volatile EXIT = 0;

/**
 * A helpfull variable set by catch exceptions, which change the return value for the main
 * function
 */
int volatile RETVAL = 0;

/**
 * Our signal handler as overwritten by our main function
 */
void sighandler(int);

/**
 * Our main loop
 */
void process(dashee::Server * server);

/**
 * This function will set our given options from command line
 */ 
void setconfig(int, char **, dashee::Config *);

/**
 * Our main function is designed to take in arguments from the command line
 * and run a UDP server. The UDP server provides a interface to the outside world
 * which can communicate and request information from our server
 *
 * @param (int)argc - The number of arguments
 * @param (char **)argv - The arguments array
 *
 * @return int - 0 on successfull shutdown and any other number for error.
 */
int main(int argc, char **argv)
{
    dashee::Server * server = NULL;

    try
    {
// Open to syslog if it is set as a daemon
#ifdef DAEMON
        dashee::Log::openSyslog(argv[0], LOG_DAEMON);
#endif
    
        // Set our sigaction
        struct sigaction act;
        memset(&act, 0, sizeof(act));
        act.sa_handler = sighandler;
        if (sigaction(SIGINT, &act, 0))
            throw new std::runtime_error("Sigaction failed");

        dashee::Config * conf = new dashee::Config();

// Start this program as a daemon so it
// can be run in background
#ifdef DAEMON
        const char * logfile = conf->get("logfile", TELEMETRYD_LOGFILE);
        const char * workingdir = conf->get("workingdir", TELEMETRYD_WORKINGDIR);
        const char * pidfile = conf->get("pidfile", TELEMETRYD_PIDFILE);

        if (!dashee::fexists(logfile))
            throw dashee::Exception("Cannot start, log file is invalid '" + (std::string)logfile + "' not found");

        // Change logging to go to stdout
        dashee::Log::openFile(logfile);

        pid_t pid;
        pid_t sid;

        // Fork our process
        pid = fork();

        // Fork failed
        if (pid < 0)
            throw dashee::Exception("fork() returned '" + dashee::itostr(pid) + "'");

        // Fork passed so parent should clean up and die
        if (pid > 0)
        {
            delete conf;
            exit(0);
        }

        //Create a new Signature Id for our child
        sid = setsid();
        if (sid < 0)
            throw dashee::Exception("sid() returned '" + dashee::itostr(sid) + "'");

        // Change working directory
        if (chdir(workingdir) < 0)
            throw dashee::Exception("Cannot change directory '" + (std::string)workingdir + "'");

        if (!dashee::createPID(pidfile, true))
            throw dashee::Exception("PID '" + (std::string)pidfile + "' file already exists");

        // Close STDIN and STDOUT
        close(STDIN_FILENO);
        close(STDERR_FILENO);
#endif
        
        // Set some generic varibles to be used later
        const unsigned int readtimeout = conf->getUInt("readtimeout", TELEMETRYD_TIMEOUT);
        const unsigned long int readtimeoutM = conf->getUInt("readtimeoutM", 0);

        // Initilize the classes
        server = new dashee::ServerUDP(conf->getUInt("port", TELEMETRYD_PORT));

        // Remove unused variables before starting the main loop
        delete conf;

        while (!EXIT)
        {
            try
            {
                if (server->read(readtimeout, readtimeoutM))
                {
                    if (!server->write("Pong"))
                        throw dashee::ExceptionServer("Write failed");
                }

                // Any timeout operations?,
                // can be performed here.
                else
                {

                }
            }
            // This only happens when a signal int is called
            // Note any cleanups must be handled here that relate
            catch (dashee::ExceptionServerSignal e)
            {
               dashee::Log::info(4, "Signal thrown from ServerUDP: %s", e.what());
               EXIT = 1;
            }
        }
    }
    catch (dashee::ExceptionConfig e)
    {
        dashee::Log::error("caught(Exception_Config): %s", e.what());
        RETVAL = -3;
    }
    catch (dashee::Exception e)
    {
        dashee::Log::error("caught(Exception): %s.", e.what());
        RETVAL = -2;
    }
    catch (std::runtime_error e)
    {
        dashee::Log::error("caught(runtime_error): %s.", e.what());
        RETVAL = -1;
    }

    dashee::Log::info(2, "Performing cleanups.");
    delete server;

    dashee::Log::info(2, "Exiting with '%d'.", RETVAL);

// Close the daemon_stream if the program
// was compiled as a daemon
#ifdef DAEMON
    dashee::Log::close();
#endif

    return RETVAL;
}

/**
 * Our signal handler as overwritten by our main function
 *
 * @param (int)sig - The signal that was thrown
 */
void sighandler(int sig)
{
    EXIT = 1;
    dashee::Log::info(3, "Signal %d called.", sig);
}
