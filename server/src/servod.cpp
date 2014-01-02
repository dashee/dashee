/** 
 * @file src/servod.cpp
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 *
 * @section DESCRIPTION 
 *
 * This program is designed to connect to the servo controller using the COM 
 * port which is usually defined by /dev/ttyACM0. It can then interface with 
 * this port by reading and writing to it. The read write protocol is defined by
 * the POLOLU board which we are using for this program
 *
 * The POLOLU Maestro board allows us to controll servo using the POLOLU 
 * protocol. This protocol is more clearly defined in Servo.h.
 *
 * Given the control of the device this program also handels a UDP server which 
 * allows forign programs to interface with it, and control the POLOLU board 
 * using a network protocol
 *
 * This server is not daemonized, as its mostly run in debug mode.
 *
 * This was developed for Linux and has never been tested in other operating 
 * systems
 */

#include <stdlib.h>
#include <sstream>
#include <string>

#include <dashee/common.h>
#include <dashee/Log.h>
#include <dashee/Config.h>
#include <dashee/daemon.h>

#include "servod/signals.h"
#include "servod/threads.h"
#include "servod/Container.h"

#define DASHEE_PIDFILE "./var/run/dashee/servod.pid"
#define DASHEE_LOGFILE "./var/log/dashee/servod.log"
#define DASHEE_WORKINGDIR "."

/**
 * Our main function is designed to take in arguments from the command line
 * and run a UDP server. The UDP server provides a interface to the outside 
 * world which can communicate and send commands to our Servo controller.
 *
 * @param argc The number of arguments
 * @param argv The arguments array
 *
 * @returns 0 on successfull shutdown and any other number for error.
 * @retval 0 Successfull process
 * @retval -5 Failed on Vehicle init
 * @retval -4 Failed on Configuration
 * @retval -3 Failed because an Exception occrred
 * @retval -2 Failed because runtime::error exception occurred
 * @retval -1 Failed because exception occured when fallback activated
 */
int main(int argc, char ** argv)
{    

    // Program exit code
    int volatile RETVAL = 0;
        
    // Create the pointers which will be initiated later
    // Initialising to NULL is important otherwise you will seg fault
    Container * container;

    try
    {
        // Create handlers to our threads
        dashee::Threads::Thread threadServer 
            = dashee::Threads::Thread(threadReadFromServer);
        dashee::Threads::Thread threadSensor 
            = dashee::Threads::Thread(threadUpdateSensors);
        dashee::Threads::Thread threadController
            = dashee::Threads::Thread(threadStepController);

        // Add to our signalThread vector, so signal can be called on these 
        // threads, incase a signal is sent to the main program
        signalThreads.push_back(&threadServer);
        signalThreads.push_back(&threadSensor);
        signalThreads.push_back(&threadController);


// Open to syslog if it is set as a daemon
#ifdef DAEMON
        dashee::Log::openSyslog(argv[0], LOG_DAEMON);
#endif
        
        container = new Container(argc, argv);
        
        // Initilize the container
        threadInitilizeContainer(container);
 
        // Load sighandler and set the config
        initSignal();

// Start this program as a daemon so it
// can be run in background
#ifdef DAEMON
	dashee::startDaemon(
                container->getConfig(), 
                DASHEE_LOGFILE, 
                DASHEE_WORKINGDIR, 
                DASHEE_PIDFILE
            );
#endif

        // Helpfull message to let the user know the service is configured
        // and will now try starting
        dashee::Log::info(
                1, 
                "Started '%s' on port %d as %d.", 
                argv[0], 
                container->getConfig()->getUInt(
                    "port", 
                    Container::SERVER_PORT
                ),
                getpid()
            );
        
        // Start our threads
        threadServer.start(static_cast<void *>(container->getServer()));
        threadSensor.start(static_cast<void *>(NULL));
        threadController.start(static_cast<void *>(container));

        // Wait for threads to gracefully stop
        threadServer.join();
        threadSensor.join();
        threadController.join();
    
        // Cleanup our refrences
        dashee::Log::info(2, "Performing cleanups.");
        delete container;

    }
    catch (dashee::ExceptionConfig e)
    {
        dashee::Log::error("caught(ExceptionConfig): %s", e.what());
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
    
    dashee::Log::info(1, "Exiting with '%d'.", RETVAL);

// Close the daemon_stream if the program
// was compiled as a daemon
#ifdef DAEMON
    dashee::Log::close();
#endif

    return RETVAL;
}
