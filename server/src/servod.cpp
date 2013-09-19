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
#include <dashee/Log.h>
#include <dashee/Common.h>
#include <dashee/ServoController/UART.h>
#include <dashee/ServoController/USB.h>
#include <dashee/ServoController/Dummy.h>
#include <dashee/Server/UDP.h>

#include "Config/Servod.h"

#define SERVO_DEVICE "/dev/ttyAMA0"
#define SERVO_DUMMY_CHANNELS 6
#define SERVER_PORT 2047u
#define SERVER_TIMEOUT 2u

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
 * @retval -3 Failed on Configuration
 * @retval -2 Failed because an Exception occrred
 * @retval -1 Failed because runtime::error exception occurred
 */
int main(int argc, char **argv)
{
    // Set our sigaction
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = sighandler;
    if (sigaction(SIGINT, &act, 0))
        throw new std::runtime_error("Sigaction failed");
    
    // Create a dummy Servo to be initiated later
    // Initialising to NULL is important otherwise you will seg fault
    dashee::ServoController *servoController = NULL;

    // Create our Config_servod, as a new pointer, as we will
    // delete it mid point to clear our heap.
    ConfigServod *conf = new ConfigServod();

    // Call our setconfig which will look for command line arguments, and set it
    // in our @conf variables. The command line arguments are read from @argv.
    // Just add a helpfull print in the end so we can see what is happening
    setconfig(argc, argv, conf);
    conf->read(conf->get("config", "etc/servod.conf"));
    conf->print();

    //Store the required variables in our stack, for easy access.
    //const char * servo = SERVO_DEVICE;
    //const unsigned int servotype = 10;
    //const unsigned int port = SERVER_PORT;
    const char * servo = conf->get("servo");
    const unsigned int servotype = conf->get_uint("servotype");
    const unsigned int port = conf->get_uint("port");
    const unsigned int readtimeout = conf->get_uint("readtimeout");
    const unsigned long int readtimeoutM = conf->get_uint("readtimeoutM", 500);

    try
    {
        // Set our servo to the COM PORT
        if (servotype == 1)
        {
            // Create a Servo
            dashee::Log::info(1, "Loading UART device '%s'.", servo);
            servoController = new dashee::ServoControllerUART(servo);
        }
        
        // Set our servo to the Binary file
        else if(servotype == 2)
        {
            dashee::Log::info(1, "Loading USB device '%s'.", servo);
            servoController = new dashee::ServoControllerUSB(servo);
        }

        // Set our servo to the Binary file
        else if(servotype == 3)
        {
            dashee::Log::info(1, "Loading Dummy device '%s'.", servo);
            servoController = new dashee::ServoControllerDummy(servo, SERVO_DUMMY_CHANNELS);
        }

        // Fail as the options must fall within the above
        else
            dashee::Log::fatal("Servotype invalid, set to %u.", servotype);
    
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
        dashee::ServerUDP serverUDP(port);
        dashee::Log::info(1, "Port initialized on %d.", port);

        // Loop through read and write our server
        while (!EXIT)
        {
            // Recieave from client and timeout after 4 seconds
            if (serverUDP.read(readtimeout, readtimeoutM))
            {
                processCommands(&serverUDP, servoController);
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
        dashee::Log::info(4, "caught(ExceptionServerSignal): %s", e.what());
    }
    catch (dashee::ExceptionConfig e)
    {
        dashee::Log::info(4, "caught(ExceptionConfig): %s", e.what());
        RETVAL = -3;
    }
    catch (dashee::Exception e)
    {
        dashee::Log::warning(1, "caught(Exception): %s.", e.what());
        RETVAL = -2;
    }
    catch (std::runtime_error e)
    {
        dashee::Log::warning(3, "caught(runtime_error): %s.", e.what());
        RETVAL = -1;
    }
    
    dashee::Log::info(4, "Performing cleanups.");
    delete servoController;

    dashee::Log::info(4, "Returning with %d.", RETVAL);
    return RETVAL;
}

/**
 *
 */
void processCommands(dashee::Server * server, dashee::ServoController * servoController)
{
    for (size_t i = 0; i < server->size(); i=i+2)
    {
        // Dashe commands are 2 bytes with the first byte driving the command and the second byte the value
        // the command byte uses the first 4 bits to set the command and the 2 4 bit to set the channel
        // ---------
        // Bitwise AND with 00000001 (1 in decimal) to zero the other command bits and if this is 1 we have a
        // command otherwise this must be a value
        if ((server->getBuffer()[i] & 1) == 1)
        {
            // @throw ExceptionServo
            try
            {
                // Bitwise AND with 00001110 (14) to zero the channel number, shift 1 as the first bit just tells us this is a command
                unsigned char command = (server->getBuffer()[i] & 14) >> 1;

                // Bitwise AND the command byte with 11110000 (240 in decimal) to zero the command number
                // then shift 4 to find the channel number as that is the last 4 bits of the command.
                unsigned char channel = (server->getBuffer()[i] & 240) >> 4;
                dashee::Log::info(3, "Command: %02d:%02d", (unsigned short int)command, (unsigned short int)channel);

                switch (command)
                {
                    case 0:
                    {
                        // -------- >> 1
                        // 0-------
                        unsigned char target = (server->getBuffer()[i+1] >> 1);

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
    int c;
    static struct option long_options[] = {
        { "servotype", 1, 0, 0 },
        { "servo", 1, 0, 0 },
        { "port", 1, 0, 0 },
        { "config", 1, 0, 0 },
        { "verbosity", 1, 0, 'v' }
    };
    int long_index = 0;
    
    while((c = getopt_long(argc, argv, "sv", long_options, &long_index)) != -1)
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
                    case 0:
                    {
                        try
                        {
                            long int servotype = dashee::Common::strtol(optarg);
                            if (servotype < 1 && servotype > 3) { dashee::Log::fatal("Invalid sevotype '%d' is not valid.", servotype); }
                            conf->set("servotype", optarg);
                            dashee::Log::info(3, "Option 'servotype' set to '%s'.",conf->get("servotype"));
                        }
                        // Servotype must be an integer
                        catch (dashee::ExceptionInvalidNumber e)
                        {
                            dashee::Log::fatal("Arg --servotype must be a number");
                        }
                        break;
                    }
                    case 1:
                        conf->set("servo", optarg);
                        dashee::Log::info(3, "Option 'servo' set to '%s'.", conf->get("servo"));
                        break;
                    case 2:
                        try
                        {
                            dashee::Common::strtol(optarg); //Do nothing, throw an exception if its not an integer
                            conf->set("port", optarg);
                            dashee::Log::info(3, "Option 'port' set to '%s'.", conf->get("port"));
                        }
                        // Port must be an integer
                        catch (dashee::ExceptionInvalidNumber e)
                        {
                            dashee::Log::fatal("Arg --port must be a number, given '%s'!", optarg);
                        }

                        break;
                    case 3:
                        conf->set("config", optarg);
                        dashee::Log::info(3, "Option 'config' set to '%s'.", conf->get("config"));
                        break;
                }
                break;

            // Give 'v' we see if optarg is set
            // If so we use its value, otherwise we increase verbosity
            // from its previous state
            case 'v':
                try
                {
                    if (optarg)
                        dashee::Log::verbosity = dashee::Common::strtol(optarg) == 0 ? 1 : dashee::Common::strtol(optarg);
                    else
                        dashee::Log::verbosity++;
                    dashee::Log::info(1, "Option 'verbosity' set to '%d'.", dashee::Log::verbosity);
                }
                // Verbosity value must be an integer
                catch(dashee::ExceptionInvalidNumber e)
                {
                    dashee::Log::fatal("Arg --verbosity must be a number, given '%s'!", optarg);
                }   
                break;

            // When something goes wrong, a '?' is returned
            case '?':
                dashee::Log::error("Option '%s' came back with '?'.", optopt);
                break;
        }
    }

    // Now that we have set our, values from the command line, we default our system values
    // Into our configs, Its is better to put this here, as -vvvvvvvvv will effect the Config class
    conf->set("servo", SERVO_DEVICE, 0);
    conf->set_uint("port", SERVER_PORT, 0);
    conf->set_uint("servotype", 1, 0);
    conf->set_uint("readtimeout", SERVER_TIMEOUT, 0);
    conf->set_uint("readtimeoutM", 0, 0);
}
