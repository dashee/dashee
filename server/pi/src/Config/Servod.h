/**
 * This is our build ontop of the Config class, This class is specific to the 
 * servod.cpp which holds our main function for the servo server, This will do special
 * config loading that is only specific to servod
 *
 * @author Shahmir Javaid
 */

#ifndef CONFIG_SERVOD_H_
#define CONFIG_SERVOD_H_

#include <dashee/Config.h>
#include <dashee/Common.h>

#include "../ServoController.h"

class ConfigServod : public dashee::Config
{
protected:
    
    // Check to see what type the value is, target, speed or acceleration;
    // and set the value for its specific command type, example default, fallback or 
    // fallbackEnabled
    bool setDefault(ServoController *, const char *, const char *, const unsigned short int &);
    bool setFallback(ServoController *, const char *, const char *, const unsigned short int &);
    bool setFallbackEnabled(ServoController *, const char *, const char *, const unsigned short int &);

public:
    
    // Initialize using the 
    ConfigServod();
    
    // Using our config, set the ServoControllers
    void setServoController(ServoController *);
        
    // Virtually destruct
    ~ConfigServod();
};

#endif
