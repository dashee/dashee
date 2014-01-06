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
#include <dashee/Hardware/Accelerometer/ADXL345.h>
#include <dashee/Hardware/Accelerometer/Dummy.h>

/**
 * Contain pointers to objects, and encapsulating loading, reloading and 
 * deleting these objects. Also with objects this class holds the pointers
 * to locks
 *
 * This is the main container class for the programs which holds pointers to 
 * all working parts of the system.
 *
 * Usage:
 *
 *     Container c(argc, argv);
 *     c.
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
    dashee::Hardware::Accelerometer * accelerometer;

    /**
     * Locks which help exclusively do operation so the outside
     * world does not interfere.
     */
    dashee::Threads::Lock * lockConfig;
    dashee::Threads::Lock * lockServer;
    dashee::Threads::Lock * lockServoController;
    dashee::Threads::Lock * lockVehicle;
    dashee::Threads::Lock * lockHardwareAccelerometer;
    
    void loadConfig();
    void loadServer();
    void loadServoController();
    void loadVehicle();
    void loadHardwareAccelerometer();

    // The functions used to reload the values
    void reloadConfig();
    void reloadServer();
    void reloadServoController();
    void reloadVehicle();
    void reloadHardwareAccelerometer();

public:

    // Public static constant variables used for defaults
    static const char * SERVOCONTROLLER_DEVICE;
    static const unsigned int SERVOCONTROLLER_TYPE;
    static const unsigned int SERVOCONTROLLER_CHANNELS;
    static const char * CONFIG;
    static const unsigned int SERVER_PORT;
    static const unsigned int SERVER_TIMEOUT;
    static const char * VEHICLE_TYPE;
    static const char * HARDWARE_ACCELEROMETER_TYPE;

    // Construct
    Container(int argc, char ** argv);

    // Set lock as
    void setLockConfig(dashee::Threads::Lock * lock);
    void setLockServer(dashee::Threads::Lock * lock);
    void setLockServoController(dashee::Threads::Lock * lock);
    void setLockVehicle(dashee::Threads::Lock * lock);
    void setLockHardwareAccelerometer(dashee::Threads::Lock * lock);

    void setConfig(dashee::Config * config);
    dashee::Config * getConfig() const;

    void setServer(dashee::Server * server);
    dashee::Server * getServer() const;

    void setServoController(dashee::ServoController * servoController);
    dashee::ServoController * getServoController() const;
    
    void setVehicle(dashee::Vehicle * vehicle);
    dashee::Vehicle * getVehicle() const;

    void setHardwareAccelerometer(
	    dashee::Hardware::Accelerometer * accelerometer
	);
    dashee::Hardware::Accelerometer * getHardwareAccelerometer() const;

    // Reload from configuration
    void reloadConfiguration();

    ~Container();
};

#endif
