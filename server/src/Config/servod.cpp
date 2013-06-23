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
 * @param s - is the handel to the ServoController
 */
void Config_servod::setServoController(ServoController * s)
{
    for(configs_it = configs.begin(); configs_it != configs.end(); ++configs_it)
    {
        // Only go through if the first 7 characters are "channel"
        if (strncmp(configs_it->first, "channel", 7) == 0)
        {
            int keyN = strlen(configs_it->first);

            // Make sure the value is atleast "channelXX-" long
            if (keyN <= 10) continue;
            
            // Make sure the value "channel[0-9][0-9]" is an integer
            if (configs_it->first[7] < 48 || configs_it->first[7] > 57) continue;
            if (configs_it->first[8] < 48 || configs_it->first[8] > 57) continue;

            // Sanity check, as we expect '-' after "channelXX", so "channelXX-"
            if (configs_it->first[9] != '-') continue;
    
            // copy the "XX" value into @channel from the string "channelXX"
            char channel[40];
            memset(channel, 0, sizeof(channel));
            memcpy(channel, configs_it->first+7, 2);

            try
            {
                long int channel_num = Common::strtol(channel);

                // if the value is "channelXX-default-" and is greater than 17 characters
                if (keyN > 17 && strncmp(configs_it->first+10, "default-", 8) == 0)
                    setDefault(s, configs_it->first+18, configs_it->second, channel_num);
                
                // if the value is "channelXX-fallbackEnabled-" and is greater than 24 characters
                else if (keyN > 24 && strncmp(configs_it->first+10, "fallbackEnabled-", 16) == 0)
                    setFallbackEnabled(s, configs_it->first+25, configs_it->second, channel_num);

                // if the value is "channelXX-fallback-" and is greater than 18 characters
                else if (keyN > 18 && strncmp(configs_it->first+10, "fallback-", 9) == 0)
                    setFallback(s, configs_it->first+19, configs_it->second, channel_num);

                else
                    Log::warning(6, "Config_servod::setServoController: channel%02d- value was found, but not valid (%s)", channel_num, configs_it->first);
            }

            catch (Exception_InvalidNumber e)
            {
                Log::warning(7, "Config_servod::setServoController: Invalid number conversion on '%s'. Exception_InvalidNumber:%s", configs_it->first, e.what());
            }
        }
    }
}

/**
 * This function will take the key value of the Config
 * and depending on that set default values for either `target`, `speed` or `acceleration`.
 *
 * @param s - Pointer to the ServoController so setting values can be accessed
 * @param what - What to set, `target`, `speed` or `acceleration`
 * @param value - the value
 * @param channel - The channel Number
 *
 * @returns bool - If the set was successfull, false any other way
 *
 */
bool Config_servod::setDefault(ServoController * s, const char * what, const char * value, const unsigned short int & channel)
{
    try
    {
        if (strcmp(what, "target") == 0)
        {
            s->setTargetDefault(channel, Common::strtol((const char *)value));
            Log::info(3, "Default target set for channel%02d to %s.", channel, value);
            return true;
        }
        else if (strcmp(what, "speed") == 0)
        {
            //s->setSpeedDefault(channel, Common::strtol((const char *)value));
            Log::info(3, "Default speed set for channel%02d to %s.", channel, value);
            return true;
        }
        else if (strcmp(what, "acceleration") == 0)
        {
            //s->setAccelerationDefault(channel, Common::strtol((const char *)value));
            Log::info(3, "Default acceleration set for channel%02d to %s.", channel, value);
            return true;
        }
            
        Log::warning(1, "Config_servod::setDefault: Invalid value '%s'.", what);
    }
    catch (Exception_InvalidNumber e)
    {
        Log::warning(1, "Config_servod::setDefault: Failed setting '%s' to '%s' NaN. Exception_InvalidNumber:%s", what, value, e.what());
    }

    return false;
}

/**
 * this Function will will set fallback values. So when the system fallbacks these 
 * are the values it will be set to
 *
 * @param s - Pointer to the ServoController so setting values can be accessed
 * @param what - What to set, `target`, `speed` or `acceleration`
 * @param value - the value
 * @param channel - The channel Number
 *
 * @returns bool - If the set was successfull, false any other way
 *
 */
bool Config_servod::setFallback(ServoController * s, const char *what, const char * value, const unsigned short int & channel)
{
    try
    {
        if (strcmp(what, "target") == 0)
        {
            s->setTargetFallback(channel, Common::strtol((const char *)value));
            Log::info(3, "Fallback target set for channel%02d to %s.", channel, value);
            return true;
        }
        else if (strcmp(what, "speed") == 0)
        {
            //s->setSpeedFallback(channel, Common::strtol((const char *)value));
            Log::info(3, "Fallback speed set for channel%02d to %s.", channel, value);
            return true;
        }
        else if (strcmp(what, "acceleration") == 0)
        {
            //s->setAccelerationFallback(channel, Common::strtol((const char *)value));
            Log::info(3, "Fallback acceleration set for channel%02d to %s.", channel, value);
            return true;
        }
            
        Log::warning(1, "Config_servod::setFallback invalid value '%s'.", what);
    }
    catch (Exception_InvalidNumber e)
    {
        Log::warning(1, "Config_servod::setFallback: Failed setting '%s' to '%s' NaN. Exception_InvalidNumber:%s", what, value, e.what());
    }

    return false;
}

/**
 * This function will enable/disable fallback for a given channel
 *
 * @param s - Pointer to the ServoController so setting values can be accessed
 * @param what - What to set, `target`, `speed` or `acceleration`
 * @param value - the value
 * @param channel - The channel Number
 *
 * @returns bool - If the set was successfull, false any other way
 *
 */
bool Config_servod::setFallbackEnabled(ServoController * s, const char *what, const char * value, const unsigned short int & channel)
{
    return false;
}

/**
 * Destruct if required
 */ 
Config_servod::~Config_servod()
{
}
