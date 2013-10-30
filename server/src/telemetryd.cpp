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
#include <dashee/daemon.h>
#include <dashee/signal.h>

#define DASHEE_PIDFILE "./var/run/dashee/telemetryd.pid"
#define DASHEE_LOGFILE "./var/log/dashee/telemetryd.log"
#define DASHEE_WORKINGDIR "."
#define DASHEE_CONFIG "./etc/dashee/telemetryd.conf"

#define DASHEE_SERVER_PORT 2047u
#define DASHEE_SERVER_TIMEOUT 2u

// Load object functions
dashee::Config * loadConfig(int argc, char ** argv);
dashee::Server * loadServer(dashee::Config * config);

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
    dashee::Config * config = NULL;

    // Program exit code
    int volatile RETVAL = 0;

    try
    {
// Open to syslog if it is set as a daemon
#ifdef DAEMON
        dashee::Log::openSyslog(argv[0], LOG_DAEMON);
#endif
    
	dashee::initSignalHandler();
        config = loadConfig(argc, argv);

// Start this program as a daemon so it
// can be run in background
#ifdef DAEMON
	dashee::startDaemon(config, DASHEE_LOGFILE, DASHEE_WORKINGDIR, DASHEE_PIDFILE);
#endif
        
        // Initilize the classes
        server = loadServer(config);

        // Remove unused variables before starting the main loop
        delete config;

        while (!dashee::EXIT)
        {
	    if (server->read())
	    {
		if (!server->write("Pong"))
		    dashee::Log::warning("Failed to write back to the server");
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
 * We need to be able to change the server behaviour using command line arguments.
 * do do that we use this function which takes in argc and argv amongst other arguments
 * other arguments are pointers so this function can modify there value
 *
 * @param argc The number of cmdline arguments.
 * @param argv The array of cmdline arguments sent
 * @param conf Pointer to the Config object used to set/get
 *
 * @return pointer to the fresh new config object
 */
dashee::Config * loadConfig(int argc, char ** argv)
{
    dashee::Config * config = new dashee::Config();

    int c;
    static struct option long_options[] = {
        { "port", 1, 0, 'p' },
        { "config", 1, 0, 'c' },
        { "verbosity", 1, 0, 'v' },
        { "logfile", 1, 0, 'l' },
        { "workingdir", 1, 0, 'w' },
        { "pidfile", 1, 0, 0 }
    };
    int long_index = 0;
    
    while((c = getopt_long(argc, argv, "c:p:v", long_options, &long_index)) != -1)
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
                    // PID file
                    case 5:
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
                    dashee::Log::verbosity = dashee::strtol(optarg) == 0 ? 1 : dashee::strtol(optarg);
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
 * Function to create a server and return its instance
 *
 * @param config The config object to load the values from
 */
dashee::Server * loadServer(dashee::Config * config)
{
    dashee::Server * server = 
	new dashee::ServerUDP(config->getUInt("port", DASHEE_SERVER_PORT));

    server->setTimeout(
            config->getUInt("readtimeout", DASHEE_SERVER_TIMEOUT), 
            config->getUInt("readtimeoutM", 0)
        );

    return server;
}
