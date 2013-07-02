/**
 * This is our build ontop of the Config class, This class is specific to the 
 * servod.cpp which holds our main function for the servo server, This will do special
 * config loading that is only specific to servod
 *
 * @author Shahmir Javaid
 */

#include "../Config.h"
#include "../ServoController.h"
#include "../Exception/Config.h"
#include "../Common.h"

#ifndef CONFIG_SERVOD_H_
#define CONFIG_SERVOD_H_

class Config_servod : public Config
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
    Config_servod();
    
    // Using our config, set the ServoControllers
    void setServoController(ServoController *);
        
    // Virtually destruct
    ~Config_servod();
};

#endif
