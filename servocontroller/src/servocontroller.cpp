#include <stdlib.h>

#include "Servo.h"
#include "Server/UDP.h"
#include "Log.h"

int main()
{
    try
    {
        Servo s("/dev/ttyACM0");

        //Print and clear any errors
        int error = s.getError();
        if (error > 0)
            fprintf(stderr, "Servo Error: %d", error);

        Server_UDP x(2047);

        //Keep listening, for stuff
        while (true)
        {
            //Recieave from client        
            if (!x.read())
            {
                perror("Recieving from client failed");
                return -1;
            }
                
            int target = atoi(x.getBuffer());

            try
            {
                
                // Print out to the server,
                printf("setTarget(1, %d)\n", target);
                //Log::info("Target is set");

                // Set the target for channel 1 as requested
                s.setTarget(1, target);
            }
            //User is out of range, only then do you print the error message
            catch (Exception_Servo& e)
            {   
                if (!x.write(e.what())) 
                    throw Exception_Server("Write failed");
                
                //Helpfull error message
                printf("Invalid Target\n");
            }
        }
    }
    catch (Exception_Servo& e)
    {
        printf("Exception Servo: %s\n", e.what());
        return -2;
    }
    
    catch (Exception_Server& e)
    {
        printf("Exception Server: %s\n", e.what());
        return -2;
    }

    catch (std::runtime_error e)
    {
        printf("Exception: %s\n", e.what());
        return -2;
    }

    //printf("Hello to the world of tomrow");
    return 0;
}
