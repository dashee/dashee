#include <stdlib.h>
#include <sstream>

#include "Servo.h"
#include "Server/UDP.h"
#include "Log.h"


std::string toString(int i)
{
    std::string s;
    std::stringstream out;
    out << i;
    return out.str();
}

int main()
{
    try
    {
        Servo s("/dev/ttyACM0");
        Log::info("Device '/dev/ttyACM0' initialized.");

        //Print and clear any errors
        int error = s.getError();
        if (error > 0)
            Log::error("Servo failed with eccode " + toString(error));

        Server_UDP x(2047);
        Log::info("Port initialized on 2047.");

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
                Log::info("setTarget(1, " + toString(target) + ")");

                // Set the target for channel 1 as requested
                s.setTarget(1, target);
            }
            //User is out of range, only then do you print the error message
            catch (Exception_Servo& e)
            {   
                //Helpfull error message
                Log::warning("Invalid Target");

                if (!x.write(e.what())) 
                    throw Exception_Server("Write failed");
            }
        }
    }
    catch (std::runtime_error e)
    {
        Log::error("EXCEPTION! " + (std::string)e.what());
        return -2;
    }

    //printf("Hello to the world of tomrow");
    return 0;
}
