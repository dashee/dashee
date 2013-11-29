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
#include <getopt.h> /* for getopts_long() */
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
    // Create the pointers which will be initiated later
    // Initialising to NULL is important otherwise you will seg fault
    dashee::ServoController *servoController = NULL;
    dashee::Server *server = NULL;
    dashee::Vehicle * vehicle = NULL;
    dashee::Config * config = NULL;

    // Program exit code
    int volatile RETVAL = 0;

    try
    {

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

/**
 * We need to be able to change the server behaviour using command line 
 * arguments. To do that we use this function which takes in argc and argv
 * and returns the added variables in our configuration
 *
 * @param argc The number of cmdline arguments.
 * @param argv The array of cmdline arguments sent
 *
 * @return pointer to the fresh new config object
 */
dashee::Config * loadConfig(int argc, char ** argv)
{
    dashee::Config * config = new dashee::Config();

    int c;
    static struct option long_options[] = {
        { "servotype", 1, 0, 0 },
        { "servo", 1, 0, 0 },
        { "port", 1, 0, 'p' },
        { "config", 1, 0, 'c' },
        { "verbosity", 1, 0, 'v' },
        { "logfile", 1, 0, 'l' },
        { "workingdir", 1, 0, 'w' },
        { "pidfile", 1, 0, 0 }
    };
    int long_index = 0;
    
    while(
            (c = getopt_long(argc, argv, "c:p:v", long_options, &long_index)) 
            != -1
        )
    {
        // switch our c, if it is 0 then it uses the long options
        switch (c)
        {
            // Use our long options
            case 0:

                // Switch using the index int, Note that the number
                // of the case x: is relevent to the long_options array above
                switch (long_index)
                {
                    // Type of Servo
                    case 0:
                        config->set(
                                "servotype", 
                                static_cast<int>(dashee::strtol(optarg))
                            );
                        break;
                    // Servo file path
                    case 1:
                        config->set("servo", optarg);
                        break;
                    // PID file
                    case 7:
                        config->set("pidfile", optarg);
                        break;
                }
                break;
            // Set the logfile location
            case 'l':
                config->set("logfile", optarg);
                break;
            // Set working directory
            case 'w':
                config->set("workingdir", optarg);
                break;
            // Give 'v' we see if optarg is set
            // If so we use its value, otherwise we increase verbosity
            // from its previous state
            case 'v':
                if (optarg)
                    dashee::Log::verbosity 
                        = dashee::strtol(optarg) == 0 
                            ? 1 : dashee::strtol(optarg);
                else
                    dashee::Log::verbosity++;
                break;
            // Represents the config file which will be read later
            case 'c':
                config->set("config", optarg);
                break;
            // Represents the port
            case 'p':
                config->set("port", static_cast<int>(dashee::strtol(optarg)));
                break;
            // When something goes wrong, a '?' is returned
            case '?':
                dashee::Log::fatal("Option '%c' requires a value.", optopt);
                break;
        }
    }
        
    config->read(config->get("config", DASHEE_CONFIG));

    return config;
}

/**
 * Load servoController from configuration.
 *
 * Check to see which type of servo is to be loaded, and
 * load it using the provided servoDevice filename.
 *
 * @param config The pointer to the config object to load from
 *
 * @throws ExceptionServoController If load fails or if the controller has 
 *  errors
 */
dashee::ServoController * loadServoController(dashee::Config * config)
{
    dashee::ServoController * servoController = NULL;

    const char * servo = config->get("servo", SERVOD_DEVICE);
    unsigned int servoChannels 
        = config->getUInt("servo-channels", SERVOD_CHANNELS);

    // Create a different servotype depending on the variable
    switch (config->getUInt("servotype", SERVOD_DEVICETYPE))
    {
        case 1:
            dashee::Log::info(1, "Loading UART device '%s'.", servo);
            servoController 
                = new dashee::ServoControllerUART(servo, servoChannels);
            break;
        case 2:
            dashee::Log::info(1, "Loading USB device '%s'.", servo);
            servoController 
                = new dashee::ServoControllerUSB(servo, servoChannels);
            break;
        case 3:
            dashee::Log::info(1, "Loading Dummy device '%s'.", servo);
            servoController = new dashee::ServoControllerDummy(
                    servo, 
                    SERVOD_CHANNELS
                );
            break;
        default:
            throw dashee::ExceptionServoController(
                    "Invalid servotype '" + 
                    dashee::itostr(
                        config->getUInt("servotype", SERVOD_DEVICETYPE)
                        ) + 
                    "'"
                );
            break;
    }

    // Print and clear errors
    int error = servoController->getError();
    if (error > 0)
        throw dashee::ExceptionServoController(
                "ServoController failed with eccode " + dashee::itostr(error)
            );

    return servoController;
}

/**
 * Function to create a server and return its instance
 *
 * @param config The config object to load the values from
 */
dashee::Server * loadServer(dashee::Config * config)
{
    dashee::Server * server 
        = new dashee::ServerUDP(config->getUInt("port", DASHEE_SERVER_PORT));

    server->setTimeout(
            config->getUInt("readtimeout", DASHEE_SERVER_TIMEOUT), 
            config->getUInt("readtimeoutM", 0)
        );

    return server;
}

/**
 * Funciton to load our vehicle
 *
 * @param config The config to read from
 * @param servoController The controller which the model requires
 */
dashee::Vehicle * loadVehicle(
        dashee::Config * config, 
        dashee::ServoController * servoController
    )
{
    const char * modelType = config->get("vehicle-type", VEHICLE_TYPE);
    dashee::Vehicle * vehicle = NULL;

    if (strcmp(modelType, "Car") == 0)
        vehicle = new dashee::VehicleCar(servoController, config);
    else if (strcmp(modelType, "MultirotorQuadX") == 0)
        vehicle = new dashee::VehicleMultirotorQuadX(servoController, config);
    else
        throw new dashee::ExceptionVehicle(
                "Invalid vehicle-type '" + 
                std::string(modelType) + 
                "'"
            );

    return vehicle;
}

/**
 * Reload our system with given variables.
 *
 * It is usefull to sometimes reload our program while it is running
 * to do this we call this function. 
 *
 * This function will also change the reload flag back to normal
 *
 * @param argc The number of cmdline arguments
 * @param argv The array with all the parameters
 * @param servoController Pointer to our ServoController
 * @param server Pointer to our Server object
 * @param vehicle Pointer to our vehicle
 */
void reloadSystem(
        int argc,
        char ** argv,
        dashee::ServoController * servoController,
        dashee::Server * server,
        dashee::Vehicle * vehicle
    )
{
    // Remove previous values
    delete servoController;

    // Load the configuration again
    dashee::Config * config = loadConfig(argc, argv);

    // Reload our server and our servoController
    servoController = loadServoController(config);
    server->setTimeout(
            config->getUInt("readtimeout", DASHEE_SERVER_TIMEOUT), 
            config->getUInt("readtimeoutM", 0)
        );

    // Change our vehicle to reflect
    vehicle = loadVehicle(config, servoController);

    // Delete as it is no longer required
    delete config;
    
    dashee::Log::info(3, "System Reloaded.");

    // Set reload flag back to normal
    dashee::RELOAD = 0;
}
