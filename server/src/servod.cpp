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
 *                     you may distribute the resulting work only under a 
 *                     licence identical to this one.
 *
 * The terms and conditions are updated at http://dashee.co.uk/license. View the
 * project site for more details
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
#include <dashee/ServoController/UART.h>
#include <dashee/ServoController/USB.h>
#include <dashee/ServoController/Dummy.h>
#include <dashee/Server/UDP.h>
#include <dashee/Vehicle/Car.h>
#include <dashee/Vehicle/Multirotor/Quad/X.h>
#include <dashee/Config.h>
#include <dashee/daemon.h>
#include <dashee/signal.h>

#include "servod/threads.h"
#include "servod/loads.h"

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

    try
    {
        // Create the pointers which will be initiated later
        // Initialising to NULL is important otherwise you will seg fault
        dashee::ServoController *servoController = NULL;
        dashee::Server *server = NULL;
        dashee::Vehicle * vehicle = NULL;
        dashee::Config * config = NULL;

        // Create handlers to our threads
        dashee::Threads::Thread threadServer 
            = dashee::Threads::Thread(threadReadFromServer);
        dashee::Threads::Thread threadSensor 
            = dashee::Threads::Thread(threadUpdateSensors);
        dashee::Threads::Thread threadController
            = dashee::Threads::Thread(threadStepController);


// Open to syslog if it is set as a daemon
#ifdef DAEMON
        dashee::Log::openSyslog(argv[0], LOG_DAEMON);
#endif
 
        // Load sighandler and set the config
        dashee::initSignalHandler();
        config = loadConfig(argc, argv);

// Start this program as a daemon so it
// can be run in background
#ifdef DAEMON
	dashee::startDaemon(
                config, 
                DASHEE_LOGFILE, 
                DASHEE_WORKINGDIR, 
                DASHEE_PIDFILE
            );
#endif
        
        // Create a UDP server
        servoController = loadServoController(config);
        server = loadServer(config);
        vehicle = loadVehicle(config, servoController);

        // Helpfull message to let the user know the service is configured
        // and will now try starting
        dashee::Log::info(
                1, 
                "Started '%s' on port %d as %d.", 
                argv[0], 
                config->getUInt("port", DASHEE_SERVER_PORT),
                getpid()
            );
        
        // No point carrying around unused memory while
        // in operation.
        delete config;

        // Start our threads
        threadServer.start(reinterpret_cast<void *>(server));
        threadSensor.start((void *)NULL);
        threadController.start((void *)NULL);
        
        // Loop through read and write our server
        while (!dashee::EXIT)
        {
            if (dashee::RELOAD)
                reloadSystem(argc, argv, servoController, server, vehicle);

            // Recieave from client and timeout after 4 seconds
            if (server->read())
            {
                try
                {
                    dashee::Log::info(
                        4, 
                        "P:%3d R:%3d Y:%3d T:%3d", 
                        vehicle->getPitch(), 
                        vehicle->getRoll(), 
                        vehicle->getYaw(), 
                        vehicle->getThrottle()
                    );

                    vehicle->transform(server);
                }
                catch (dashee::ExceptionVehicle e)
                {
                    dashee::Log::warning(
                            1, 
                            "caught(ExceptionMode): %s", 
                            e.what()
                        );
                    vehicle->fallback();
                }
            }
            else
            {
                vehicle->fallback();
                dashee::Log::info(1, "TIMEOUT");
            }
        }

        // Wait for threads to gracefully stop
        threadServer.join();
        threadSensor.join();
        threadController.join();
        
        // Cleanup our refrences
        dashee::Log::info(2, "Performing cleanups.");
        delete servoController;
        delete server;
        delete vehicle;
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
