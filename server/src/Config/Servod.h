/**
 * @file src/Config/Servod.h
 * @author Shahmir Javaid
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. In general
 * you are free to copy, distribute, display, and perform the work, 
 * you are also free to make derivative works, under the following conditions:
 *  - Attribution    — You must give dashee's author credit.
 *  - Non-Commercial - You may not use this dashee for commercial 
 *                     purposes without permission.
 *  - Share Alike    — If you alter, transform, or build upon this work, 
 *                     you may distribute the resulting work only under a licence 
 *                     identical to this one.
 *
 * The terms and conditions are updated at http://dashee.co.uk/license. View the
 * project site for more details
 */

#ifndef CONFIG_SERVOD_H_
#define CONFIG_SERVOD_H_

#include <dashee/Config.h>
#include <dashee/ServoController.h>

/**
 * Configuration for the servod program.
 *
 * This is our build ontop of the Config class, This class is specific to the 
 * servod.cpp which holds our main function for the servo server, This will do special
 * config loading that is only specific to servod
 */
class ConfigServod : public dashee::Config
{
protected:
    
public:
    
    // Initialize using the 
    ConfigServod();
    
    // Using our config, set the ServoControllers
    void setServoController(dashee::ServoController *);
    void setModel(dashee::Model *);
        
    // Virtually destruct
    ~ConfigServod();
};

#endif
