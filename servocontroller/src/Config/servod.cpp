#include "servod.h"

/** 
 * Initialize our maps, and internal variables
 */
Config_servod::Config_servod() : Config()
{
}

/** 
 * This function goes through the configs map and looks for in the shape of
 * channelXX-default-target, where "channel" is the identifier, the "XX" is a 
 * number from 0-99, we then hit a seperator "-" what comes exactly after
 * the dash is the struct value from @Servo class. In our example default will
 * go to Servo::default. We then get another seperator, which is used as the value
 * of the struct, so in the example above we are setting Servo::defalt.target to the value
 * where the value is an integer
 *
 * But to actually set the value we know the Servo from the "XX" number, so it will be
 * ServoController::setDefaultTarget(<channel>, <value>), if channelXX-default-speed is 
 * found then we run ServoController::setDefaultSpeed(<channel>, <value>)
 *
 * In some cases, the value channelXX-fallbackEnabled-target=1 will call:
 *   ServoController::setFallbackenabled::target(<channel>, <value>)
 *
 * @param (ServoController *)s - is the handel to the servo
 */
void Config_servod::setServoController(ServoController * s)
{
    for(configs_it = configs.begin(); configs_it != configs.end(); ++configs_it)
    {
        // Only go through if the first 7 characters are "channel"
        if (strncmp(configs_it->first, "channel", 7) == 0)
        {
            int keyN = strlen(configs_it->first);

            // Make sure the value is actually "channelXX-" long
            if (keyN <= 10) continue;
            
            // Make sure the value "channel[0-9][0-9]" is in the range
            if (configs_it->first[7] < 48 || configs_it->first[7] > 57) continue;
            if (configs_it->first[8] < 48 || configs_it->first[8] > 57) continue;

            // Sanity check, as we expect '-' after "channelXX", so "channelXX-"
            if (configs_it->first[9] != '-') continue;
    
            // copy the "XX" value into @channel from the string "channelXX"
            char temp[25];
            memset(temp, 0, sizeof(temp)*25);
            memcpy(temp, configs_it->first+7, 2);
            int channel = atoi(temp);
            
            // if the value is "channelXX-default-" and is greater than 17 characters
            if (keyN > 17 && strncmp(configs_it->first+10, "default-", 8))
            {
                //Get this to work
            }

            Log::info(1, "-------Found channel %d", channel);
        }
    }

    //foreach
}

/**
 * Destruct if required
 */ 
Config_servod::~Config_servod()
{
}
