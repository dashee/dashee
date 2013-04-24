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

#include "Servo.h"
#include "Server/UDP.h"
#include "Log.h"

#define SERVO_DEVICE "/dev/ttyACM0"
#define SERVER_PORT 2047

int main()
{

    // @throw Exception_Servo
    // @throw Exception_Server
    // @throw std::runtime_error
    try
    {
        // Create a Servo
        Servo s(SERVO_DEVICE);
        Log::info(1, "Device '%s' initialized.", SERVO_DEVICE);

        // Print and clear any Servo specific errors
        int error = s.getError();
        if (error > 0)
            Log::error("Servo failed with eccode %d", error);
        
        // Create a UDP server
        Server_UDP x(SERVER_PORT);
        Log::info(1, "Port initialized on %d.", SERVER_PORT);

        // Loop through read and write our server
        while (true)
        {
            // Recieave from client        
            if (!x.read())
                Log::fatal("Recieving from client failed");
                
            int target = atoi(x.getBuffer());
        
            // @throw Exception_Servo
            try
            {
                // Print out to the server,
                Log::info(1, "setTarget(1, %d)" ,target);

                // Set the target for channel 1 as requested
                s.setTarget(1, target);
            }
            // User is out of range, only then do you print the error message
            catch (Exception_Servo& e)
            {   
                // Helpfull error message
                Log::warning(1, "Invalid Target %d", target);

                if (!x.write("Invalid Target\n")) 
                    throw Exception_Server("Write failed");
            }
        }
    }
    catch (Exception_Servo e)
    {
        Log::fatal("EXCEPTION! %s", e.what());
    }
    catch (std::runtime_error e)
    {
        Log::fatal("EXCEPTION! %s", e.what());
    }

    return 0;
}
