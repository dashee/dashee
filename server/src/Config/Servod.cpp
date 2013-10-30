#include "Servod.h"

/** 
 * Construct.
 *
 * Call our parent class constructor, internally do nothing.
 */
ConfigServod::ConfigServod() : Config()
{
}

void ConfigServod::setModel(dashee::Model * model)
{
}

/** 
 * Set the servoController variable.
 *
 * For each channelXX value found, use XX as the servo channel number and the
 * value as the target number
 *
 * @param s is the handel to the ServoController
 */
void ConfigServod::setServoController(dashee::ServoController * s)
{
    for(
	std::map<const char *, char *>::iterator it = configs.begin();
       	it != configs.end();
       	++it
    )
    {
        // Only go through if the first 7 characters are "channel"
        if (strncmp(it->first, "channel", 7) == 0)
        {
            int keyN = strlen(it->first);

            // Make sure the value is atleast "channelXX-" long
            if (keyN <= 10) continue;
            
            // Make sure the value "channel[0-9][0-9]" is an integer
            if (it->first[7] < 48 || it->first[7] > 57) continue;
            if (it->first[8] < 48 || it->first[8] > 57) continue;
    
            // copy the "XX" value into @channel from the string "channelXX"
            char channel[40];
            memset(channel, 0, sizeof(channel));
            memcpy(channel, it->first+7, 2);

	    s->setTargetDefault(
		    dashee::strtol(channel), 
		    dashee::strtol((const char *)it->second)
		);
        }
    }
}

/**
 * Destruct.
 *
 * Does nothing
 */ 
ConfigServod::~ConfigServod()
{
}
