/**
 * @file src/servod/Controller.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_SERVOD_CONTROLLER_H_
#define DASHEE_SERVOD_CONTROLLER_H_

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

#include "Container.h"

/**
 * Our main controller designed to perform actions on input, do automation
 * if no input and finally do some balancing
 */
class Controller
{
private:

protected:

    /**
     * Pointer to our container object
     */
    Container * container;

public:

    // Construct
    Controller(Container * container);

    void setContainer(Container * container);
    Container * getContainer();

    //void actionReadinput();
    //void actionAutomate();
    //void actionFallback();
    
    // Function which steps 
    void step();

    ~Controller();
};

#endif
