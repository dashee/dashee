#include <stdlib.h>
#include <sstream>

#include "Servo.h"
#include "Server/UDP.h"
#include "Log.h"

#define SERVO_DEVICE "/dev/ttyACM0"
#define SERVER_PORT 2047

int main()
{
    try
    {
        Servo s(SERVO_DEVICE);
        Log::info(1, "Device '%s' initialized.", SERVO_DEVICE);

        //Print and clear any errors
        int error = s.getError();
        if (error > 0)
            Log::error("Servo failed with eccode %d", error);

        Server_UDP x(SERVER_PORT);
        Log::info(1, "Port initialized on %d.", SERVER_PORT);

        //Keep listening, for stuff
        while (true)
        {
            //Recieave from client        
            if (!x.read())
            {
                Log::error("Recieving from client failed");
                return -1;
            }
                
            int target = atoi(x.getBuffer());

            try
            {
                // Print out to the server,
                Log::info(1, "setTarget(1, %d)" ,target);

                // Set the target for channel 1 as requested
                s.setTarget(1, target);
            }
            //User is out of range, only then do you print the error message
            catch (Exception_Servo& e)
            {   
                //Helpfull error message
                Log::warning(1, "Invalid Target %d", target);

                if (!x.write("Invalid Target\n")) 
                    throw Exception_Server("Write failed");
            }
        }
    }
    catch (Exception_Servo e)
    {
        Log::error("EXCEPTION! %s", e.what());
        return -2;
    }
    catch (std::runtime_error e)
    {
        Log::error("EXCEPTION! %s", e.what());
        return -2;
    }

    return 0;
}
