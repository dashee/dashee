/**
 * This is our build ontop of the Config class, This class is specific to the 
 * servod.cpp which holds our main function for the servo server, This will do special
 * config loading that is only specific to servod
 *
 * @author Shahmir Javaid
 */

#include "../Config.h"
#include "../ServoController.h"

#ifndef CONFIG_SERVOD_H_
#define CONFIG_SERVOD_H_

class Config_servod : public Config
{
protected:

public:
    
    // Initialize using the 
    Config_servod();
    
    // Using our config, set the ServoControllers
    void setServoController(ServoController * s);
        
    // Virtually destruct
    ~Config_servod();
};

#endif
