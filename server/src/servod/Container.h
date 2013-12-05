/**
 * @file src/servod/Container.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_SERVOD_CONTAINER_H_
#define DASHEE_SERVOD_CONTAINER_H_

#include <getopt.h> /* for getopts_long() */

#include <dashee/Log.h>
#include <dashee/Config.h>
#include <dashee/Exception.h>
#include <dashee/Threads/Exception.h>
#include <dashee/Threads/Lock.h>
#include <dashee/Threads/Scope.h>
#include <dashee/Server/UDP.h>
#include <dashee/ServoController/USB.h>
#include <dashee/ServoController/UART.h>
#include <dashee/ServoController/Dummy.h>
#include <dashee/Vehicle.h>
#include <dashee/Vehicle/Car.h>
#include <dashee/Vehicle/Multirotor/Quad/X.h>

/**
 * Contain pointers to objects, and encapsulating loading, reloading and 
 * deleting these objects. Also with objects this class holds the pointers
 * to locks
 *
 * This is the main container class for the programs which holds pointers to 
 * all oired by the main brain of the program
 */
class Container
{
private:
    int argc;
    char ** argv;

protected:

    /**
     * List of generic variables the Controller is responsible for, Such as:
     *
     *  - Config - The loaded configuration
     *  - Server - The loaded server
     *  - ServoController - The loaded ServoController
     */
    dashee::Config * config;
    dashee::Server * server;
    dashee::ServoController * servoController;
    dashee::Vehicle * vehicle;

    /**
     * Locks which help exclusively do operation so the outside
     * world does not interfear.
     */
    dashee::Threads::Lock * lockConfig;
    dashee::Threads::Lock * lockServer;
    dashee::Threads::Lock * lockServoController;
    dashee::Threads::Lock * lockVehicle;
    
    void loadConfig();
    void loadServer();
    void loadServoController();
    void loadVehicle();

    // The functions used to reload the values
    void reloadConfig();
    void reloadServer();
    void reloadServoController();
    void reloadVehicle();

public:

    // Public static constant variables used for defaults
    static const char * SERVOCONTROLLER_DEVICE;
    static const unsigned int SERVOCONTROLLER_TYPE;
    static const unsigned int SERVOCONTROLLER_CHANNELS;
    static const char * CONFIG;
    static const unsigned int SERVER_PORT;
    static const unsigned int SERVER_TIMEOUT;
    static const char * VEHICLE_TYPE;

    // Construct
    Container(int argc, char ** argv);

    // Set lockas
    void setLockConfig(dashee::Threads::Lock * lock);
    void setLockServer(dashee::Threads::Lock * lock);
    void setLockServoController(dashee::Threads::Lock * lock);
    void setLockVehicle(dashee::Threads::Lock * locl);

    void setConfig(dashee::Config * config);
    dashee::Config * getConfig();

    void setServer(dashee::Server * server);
    dashee::Server * getServer();

    void setServoController(dashee::ServoController * servoController);
    dashee::ServoController * getServoController();
    
    void setVehicle(dashee::Vehicle * vehicle);
    dashee::Vehicle * getVehicle();

    // Reload from configuration
    void reloadConfiguration();

    ~Container();
};

#endif
