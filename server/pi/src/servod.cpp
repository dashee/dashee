/** 
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
 *
 * @author Shahmir Javaid
 */

#include <stdlib.h>
#include <sstream>
#include <getopt.h> /* for getopts_long() */

#include "ServoController/UART.h"
#include "ServoController/USB.h"
#include "ServoController/Dummy.h"
#include "Server/UDP.h"
#include "Log.h"
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
void setconfig(int, char **, Config *);

/**
 * Our main function is designed to take in arguments from the command line
 * and run a UDP server. The UDP server provides a interface to the outside world
 * which can communicate and send commands to our Servo controller.
 *
 * @param (int)argc - The number of arguments
 * @param (char **)argv - The arguments array
 *
 * @return int - 0 on successfull shutdown and any other number for error.
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
    ServoController *servoController = NULL;

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
            Log::info(1, "Loading UART device '%s'.", servo);
            servoController = new ServoControllerUART(servo);
        }
        
        // Set our servo to the Binary file
        else if(servotype == 2)
        {
            Log::info(1, "Loading USB device '%s'.", servo);
            servoController = new ServoControllerUSB(servo);
        }

        // Set our servo to the Binary file
        else if(servotype == 3)
        {
            Log::info(1, "Loading Dummy device '%s'.", servo);
            servoController = new ServoControllerDummy(servo, SERVO_DUMMY_CHANNELS);
        }

        // Fail as the options must fall within the above
        else
            Log::fatal("Servotype invalid, set to %u.", servotype);
    
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
            Log::error("Servo failed with eccode %d", error);
        
        // Create a UDP server
        Server_UDP udp(port);
        Log::info(1, "Port initialized on %d.", port);

        // Loop through read and write our server
        while (!EXIT)
        {
            // Recieave from client and timeout after 4 seconds
            if (udp.read(readtimeout, readtimeoutM))
            {
                //if (EXIT) { break; }
                
                // ---------
                // 000000001 &
                // 00000000-
                if ((udp.getBuffer()[0] & 1) == 1)
                {   
                    // @throw Exception_Servo
                    try
                    {
                        // --------
                        // 00001110 & 14
                        // 0000---0 >> 1
                        // 00000---
                        unsigned char command = (udp.getBuffer()[0] & 14) >> 1;

                        // --------
                        // 11110000 & 240
                        // ----0000 >> 4
                        // 0000----
                        unsigned char channel = (udp.getBuffer()[0] & 240) >> 4;
                        Log::info(3, "Command: %02d:%02d", (unsigned short int)command, (unsigned short int)channel);

                        switch (command)
                        {
                            case 0:
                            {
                                // -------- >> 1
                                // 0-------
                                unsigned char target = (udp.getBuffer()[1] >> 1);

                                // Set the target for channel 1 as requested
                                //servoController->setTarget(1, target);
                                Log::info(2, "setTarget(%d, %d)" , (unsigned short int)channel, (unsigned short int)target);
                                servoController->setTarget(channel, target);
                                break;
                            }
                            case 1:
                                Log::info(2, "setSpeed(%d)", (unsigned short int)channel);
                                break;
                            case 2:
                                Log::info(2, "setAcceleration(%d)", (unsigned short int)channel);
                                break;
                            case 3:
                                    Log::info(3, "pong");
                                    if (!udp.write("\x80"))
                                        throw Exception_ServoController("Pong write failed");
                                    break;
                            default:
                                throw Exception_Servo("Invalid Command!");
                                break;
                                
                        }
                    }
                    // User is out of range, only then do you print the error message, Otherwise,
                    // other exceptions are errors, 
                    // 
                    // TODO Make this Exception_Servo_Outofrange, for clairty
                    // so we dont catch fatal errors
                    catch (Exception_ServoController e)
                    {   
                        Log::warning(1, e.what());
                        if (!udp.write(e.what())) 
                            throw Exception_Server("Write failed");
                    }
                }
            }

            // Timeout and set the servo's in fallback mode
            else
            {
                servoController->fallback();
                Log::info(3, "read() timeout");
            }
        }
    }
    catch (Exception_Server_Signal e)
    {
        Log::info(4, "caught(Exception_Server_Signal): %s", e.what());
        RETVAL = -4;
    }
    catch (Exception_Config e)
    {
        Log::info(4, "caught(Exception_Config): %s", e.what());
        RETVAL = -3;
    }
    catch (Exception e)
    {
        Log::warning(1, "caught(Exception): %s.", e.what());
        RETVAL = -2;
    }
    catch (std::runtime_error e)
    {
        Log::warning(3, "caught(runtime_error): %s.", e.what());
        RETVAL = -1;
    }
    
    Log::info(4, "Performing cleanups.");
    delete servoController;

    Log::info(4, "Returning with %d.", RETVAL);
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
    Log::info(3, "Signal %d called.", sig);
}

/**
 * We need to be able to change the server behaviour using command line arguments.
 * do do that we use this function which takes in argc and argv amongst other arguments
 * other arguments are pointers so this function can modify there value
 *
 * @param (int)argc - The number of arguments
 * @param (char **)argv - The arguments array
 * @param (unsigned int *)servotype - The type of servo, 1 for USB, 2 for FILE
 * @param (char **)servo - The file name for the servo
 * @param (unsigned int *)port - The port the server will run on
 */
void setconfig(int argc, char ** argv, Config *conf)
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
                            long int servotype = Common::strtol(optarg);
                            if (servotype < 1 && servotype > 3) { Log::fatal("Invalid sevotype '%d' is not valid.", servotype); }
                            conf->set("servotype", optarg);
                            Log::info(3, "Option 'servotype' set to '%s'.",conf->get("servotype"));
                        }
                        // Servotype must be an integer
                        catch (Exception_InvalidNumber e)
                        {
                            Log::fatal("Arg --servotype must be a number");
                        }
                        break;
                    }
                    case 1:
                        conf->set("servo", optarg);
                        Log::info(3, "Option 'servo' set to '%s'.", conf->get("servo"));
                        break;
                    case 2:
                        try
                        {
                            Common::strtol(optarg); //Do nothing, throw an exception if its not an integer
                            conf->set("port", optarg);
                            Log::info(3, "Option 'port' set to '%s'.", conf->get("port"));
                        }
                        // Port must be an integer
                        catch (Exception_InvalidNumber e)
                        {
                            Log::fatal("Arg --port must be a number, given '%s'!", optarg);
                        }

                        break;
                    case 3:
                        conf->set("config", optarg);
                        Log::info(3, "Option 'config' set to '%s'.", conf->get("config"));
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
                        Log::verbosity = Common::strtol(optarg) == 0 ? 1 : Common::strtol(optarg);
                    else
                        Log::verbosity++;
                    Log::info(1, "Option 'verbosity' set to '%d'.", Log::verbosity);
                }
                // Verbosity value must be an integer
                catch(Exception_InvalidNumber e)
                {
                    Log::fatal("Arg --verbosity must be a number, given '%s'!", optarg);
                }   
                break;

            // When something goes wrong, a '?' is returned
            case '?':
                Log::error("Option '%s' came back with '?'.", optopt);
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
