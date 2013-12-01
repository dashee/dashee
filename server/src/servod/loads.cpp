#include "loads.h"

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
        { "servo-type", 1, 0, 0 },
        { "servo-name", 1, 0, 0 },
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
                                "servo-type", 
                                static_cast<int>(dashee::strtol(optarg))
                            );
                        break;
                    // Servo file path
                    case 1:
                        config->set("servo-name", optarg);
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

    const char * servoName = config->get("servo-name", SERVOD_DEVICE);
    unsigned int servoChannels 
        = config->getUInt("servo-channels", SERVOD_CHANNELS);

    // Create a different servo-type depending on the variable
    switch (config->getUInt("servo-type", SERVOD_DEVICETYPE))
    {
        case 1:
            dashee::Log::info(1, "Loading UART device '%s'.", servoName);
            servoController 
                = new dashee::ServoControllerUART(servoName, servoChannels);
            break;
        case 2:
            dashee::Log::info(1, "Loading USB device '%s'.", servoName);
            servoController 
                = new dashee::ServoControllerUSB(servoName, servoChannels);
            break;
        case 3:
            dashee::Log::info(1, "Loading Dummy device '%s'.", servoName);
            servoController = new dashee::ServoControllerDummy(
                    servoName, 
                    SERVOD_CHANNELS
                );
            break;
        default:
            throw dashee::ExceptionServoController(
                    "Invalid servo-type '" + 
                    dashee::itostr(
                        config->getUInt("servo-type", SERVOD_DEVICETYPE)
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

