/** 
 * @file include/dashee/Common.h
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
 * This program is designed to connect to the servo controller using the COM port
 * which is usually defined by /dev/ttyACM0. It can then interface with this port 
 * by reading and writing to it. The read write protocol is defined by the POLOLU
 * board which we are using for this program
 *
 * The POLOLU Maestro board allows us to controll servo using the POLOLU protocol
 * This protocol is more clearly defined in Servo.h.
 *
 * Given the control of the device this program also handels a UDP server which allows
 * forign programs to interface with it, and control the POLOLU board using a network
 * protocol
 *
 * This server is not daemonized, as its mostly run in debug mode.
 *
 * This was developed for Linux and has never been tested in other operating systems
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

#include "Config/Servod.h"

#define SERVOD_DEVICE "/dev/ttyAMA0"
#define SERVOD_DEVICETYPE 1
#define SERVOD_DUMMY_CHANNELS 6
#define SERVOD_PORT 2047u
#define SERVOD_TIMEOUT 2u
#define SERVOD_LOGFILE "./var/log/dashee/servod.log"
#define SERVOD_CONFIG "./etc/dashee/servod.conf"
#define SERVOD_PIDFILE "./var/run/dashee/servod.pid"
#define SERVOD_WORKINGDIR "."

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
 * This function will set our given options from command line, See intilization for full details
 */ 
void setconfig(int, char **, dashee::Config *);

/**
 * Read the commnds returned from the server
 * and run them appropriatly
 */
void processCommands(dashee::Server *, dashee::ServoController *);

/**
 * Our main function is designed to take in arguments from the command line
 * and run a UDP server. The UDP server provides a interface to the outside world
 * which can communicate and send commands to our Servo controller.
 *
 * @param argc The number of arguments
 * @param argv The arguments array
 *
 * @returns 0 on successfull shutdown and any other number for error.
 * @retval 0 Successfull process
 * @retval -4 Failed on Configuration
 * @retval -3 Failed because an Exception occrred
 * @retval -2 Failed because runtime::error exception occurred
 * @retval -1 Failed because exception occured when fallback activated
 */
int main(int argc, char **argv)
{    
    // Create the pointers which will be initiated later
    // Initialising to NULL is important otherwise you will seg fault
    dashee::ServoController *servoController = NULL;
    dashee::Server *server = NULL;

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
        if (sigaction(SIGTERM, &act, 0))
            throw new std::runtime_error("Sigaction failed");

        // Create our Config_servod, as a new pointer, as we will
        // delete it mid point to clear our heap.
        ConfigServod *conf = new ConfigServod();

        // Call our setconfig which will look for command line arguments, and set it
        // in our @conf variables. The command line arguments are read from @argv.
        // Just add a helpfull print in the end so we can see what is happening
        setconfig(argc, argv, conf);
        conf->read(conf->get("config", "etc/servod.conf"));
        //conf->print();

        //Store the required variables in our stack, for easy access.
        //const char * servo = SERVO_DEVICE;
        //const unsigned int servotype = 10;
        //const unsigned int port = SERVER_PORT;
        const char * servo = conf->get("servo");
        const unsigned int servotype = conf->getUInt("servotype");
        const unsigned int port = conf->getUInt("port");
        const unsigned int readtimeout = conf->getUInt("readtimeout", SERVOD_TIMEOUT);
        const unsigned long int readtimeoutM = conf->getUInt("readtimeoutM", 0);

// Start this program as a daemon so it
// can be run in background
#ifdef DAEMON
        const char * logfile = conf->get("logfile");
        const char * workingdir = conf->get("workingdir");
        const char * pidfile = conf->get("pidfile");

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

        // Helpfull message to let the user know the service is configured
        // and will now try starting
        dashee::Log::info(1, "Starting '%s'.", argv[0]);

        // Create a different servotype depending on the variable
        switch (servotype)
        {
            case 1:
                dashee::Log::info(1, "Loading UART device '%s'.", servo);
                servoController = new dashee::ServoControllerUART(servo);
                break;
            case 2:
                dashee::Log::info(1, "Loading USB device '%s'.", servo);
                servoController = new dashee::ServoControllerUSB(servo);
                break;
            case 3:
                dashee::Log::info(1, "Loading Dummy device '%s'.", servo);
                servoController = new dashee::ServoControllerDummy(servo, SERVOD_DUMMY_CHANNELS);
                break;
            default:
                dashee::Log::fatal("Servotype invalid, set to %u.", servotype);
                break;
        }
    
        // Set the Servocontroller, from the config file
        // and then delete the variable, as we dont use it any more
        // so no point utilizing the heap, See Congfig_servod::setServoController for
        // detailed explaination for this
        conf->setServoController(servoController);
        delete conf;

        // Print and clear any Servo specific errors.
        // This should not be fatal, as the servo only stores last errors.
        // Which should be printed
        int error = servoController->getError();
        if (error > 0)
            dashee::Log::error("Servo failed with eccode %d", error);
        
        // Create a UDP server
        server = new dashee::ServerUDP(port);
        dashee::Log::info(1, "Port initialized on %d.", port);

        // Loop through read and write our server
        while (!EXIT)
        {
            // Recieave from client and timeout after 4 seconds
            if (server->read(readtimeout, readtimeoutM))
            {
                processCommands(server, servoController);
            }

            // Timeout and set the servo's in fallback mode
            else
            {
                servoController->fallback();
                dashee::Log::info(3, "read() timeout");
            }
        }
    }
    catch (dashee::ExceptionServerSignal e)
    {
        dashee::Log::error("caught(ExceptionServerSignal): %s", e.what());
    }
    catch (dashee::ExceptionConfig e)
    {
        dashee::Log::error("caught(ExceptionConfig): %s", e.what());
        RETVAL = -4;
    }
    catch (dashee::Exception e)
    {
        dashee::Log::error("caught(Exception): %s.", e.what());
        RETVAL = -3;
    }
    catch (std::runtime_error e)
    {
        dashee::Log::error("caught(runtime_error): %s.", e.what());
        RETVAL = -2;
    }
    
    // Make sure to run the fallbackmode so the host is not left
    // on full power
    if (servoController != NULL)
    {
        try
        {
            dashee::Log::info(3, "Calling fallback, before exiting to the host");
            servoController->fallback();
        }
        catch (dashee::Exception e)
        {
            dashee::Log::error("Clean up fallback threw an exception: %s", e.what());
            RETVAL = -1;
        }
    }
    
    dashee::Log::info(2, "Performing cleanups.");
    delete servoController;
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
 * Read from server and set the servocontroller.
 *
 * @param server The pointer to the server variable
 * @param servoController The pointer to the servocontroller
 *
 * @throws ExceptionServer when write fails
 */
void processCommands(dashee::Server *server, dashee::ServoController *servoController)
{
    //dashee::Log::info(5, "recieved[%d] = { %x }", server->size(), server->getBuffer());
    dashee::Log::info(5, "recieved[%d]", server->size());

    for (unsigned int i = 0; i < server->size(); i+=2)
    {
        // Dashe commands are 2 bytes with the first byte driving the command and the second byte the value
        // the command byte uses the first 4 bits to set the command and the 2 4 bit to set the channel
        // ---------
        // Bitwise AND with 00000001 (1 in decimal) to zero the other command bits and if this is 1 we have a
        // command otherwise this must be a value
        if ((server->getBufferByte(i) & 1) == 1)
        {
            try
            {
                // Bitwise AND with 00001110 (14) to zero the channel number, shift 1 as the first bit just tells us this is a command
                unsigned char command = (server->getBufferByte(i) & 14) >> 1;

                // Bitwise AND the command byte with 11110000 (240 in decimal) to zero the command number
                // then shift 4 to find the channel number as that is the last 4 bits of the command.
                unsigned char channel = (server->getBufferByte(i) & 240) >> 4;
                dashee::Log::info(3, "Command: %02d:%02d", (unsigned short int)command, (unsigned short int)channel);

                switch (command)
                {
                    case 0:
                    {
                        // -------- >> 1
                        // 0-------
                        unsigned char target = (server->getBufferByte(i+1) >> 1);

                        // Set the target for channel 1 as requested
                        //servoController->setTarget(1, target);
                        dashee::Log::info(2, "setTarget(%d, %d)" , (unsigned short int)channel, (unsigned short int)target);
                        servoController->setTarget(channel, target);
                        break;
                    }
                    case 1:
                        dashee::Log::info(2, "setSpeed(%d)", (unsigned short int)channel);
                        break;
                    case 2:
                        dashee::Log::info(2, "setAcceleration(%d)", (unsigned short int)channel);
                        break;
                    case 3:
                            dashee::Log::info(3, "pong");
                            if (!server->write("\x80"))
                                throw dashee::ExceptionServoController("Pong write failed");
                            break;
                    default:
                        throw dashee::ExceptionServo("Invalid Command!");
                        break;
                        
                }
            }
            // User is out of range, only then do you print the error message, Otherwise,
            // other exceptions are errors, 
            // 
            // TODO Make this ExceptionServo_Outofrange, for clairty
            // so we dont catch fatal errors
            catch (dashee::ExceptionServoController e)
            {   
                dashee::Log::warning(1, e.what());
                if (!server->write(e.what())) 
                    throw dashee::ExceptionServer("Write failed");
            }
        }
    }
}

/**
 * Our signal handler as overwritten by our main function
 *
 * @param sig The signal that was thrown
 */
void sighandler(int sig)
{
    EXIT = 1;
    dashee::Log::info(3, "Signal %d called.", sig);
}

/**
 * We need to be able to change the server behaviour using command line arguments.
 * do do that we use this function which takes in argc and argv amongst other arguments
 * other arguments are pointers so this function can modify there value
 *
 * @param argc The number of cmdline arguments.
 * @param argv The array of cmdline arguments sent
 * @param conf Pointer to the Config object used to set/get
 */
void setconfig(int argc, char ** argv, dashee::Config *conf)
{
    // Default some configuration values
    conf->set("servo", SERVOD_DEVICE, 0);
    conf->set("port", SERVOD_PORT, 0);
    conf->set("servotype", SERVOD_DEVICETYPE, 0);
    conf->set("readtimeout", SERVOD_TIMEOUT, 0);
    conf->set("readtimeoutM", 0, 0);
    conf->set("config", SERVOD_CONFIG, 0);
    conf->set("logfile", SERVOD_LOGFILE, 0);
    conf->set("workingdir", SERVOD_WORKINGDIR, 0);
    conf->set("pidfile", SERVOD_PIDFILE, 0);

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
                    // Type of Servo
                    case 0:
                    {
                        long int servotype = dashee::strtol(optarg);
                        if (servotype < 1 && servotype > 3) { dashee::Log::fatal("Invalid sevotype '%d' is not valid.", servotype); }
                        conf->set("servotype", optarg);
                        dashee::Log::info(3, "Option 'servotype' set to '%s'.",conf->get("servotype"));
                        break;
                    }
                    // Servo file path
                    case 1:
                        conf->set("servo", optarg);
                        dashee::Log::info(3, "Option 'servo' set to '%s'.", conf->get("servo"));
                        break;
                    // PID file
                    case 7:
                        conf->set("pidfile", optarg);
                        dashee::Log::info(3, "Option 'pidfile' set to '%s'.", conf->get("pidfile"));
                        break;
                }
                break;
            // Set the logfile location
            case 'l':
                conf->set("logfile", optarg);
                dashee::Log::info(3, "Option 'logfile' set to '%s'.", conf->get("workingdir"));
                break;
            // Set working directory
            case 'w':
                conf->set("workingdir", optarg);
                dashee::Log::info(3, "Option 'workingdir' set to '%s'.", conf->get("workingdir"));
                break;
            // Give 'v' we see if optarg is set
            // If so we use its value, otherwise we increase verbosity
            // from its previous state
            case 'v':
                if (optarg)
                    dashee::Log::verbosity = dashee::strtol(optarg) == 0 ? 1 : dashee::strtol(optarg);
                else
                    dashee::Log::verbosity++;
                dashee::Log::info(1, "Option 'verbosity' set to '%d'.", dashee::Log::verbosity);
                break;
            // Represents the config file which will be read later
            case 'c':
                conf->set("config", optarg);
                dashee::Log::info(3, "Option 'config' set to '%s'.", conf->get("config"));
                break;
            // Represents the port
            case 'p':
                dashee::strtol(optarg); //Do nothing, throw an exception if its not an integer
                conf->set("port", optarg);
                dashee::Log::info(3, "Option 'port' set to '%s'.", conf->get("port"));
                break;
            // When something goes wrong, a '?' is returned
            case '?':
                dashee::Log::fatal("Option '%c' requires a value.", optopt);
                break;
        }
    }
}
