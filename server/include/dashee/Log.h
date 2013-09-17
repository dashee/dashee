/**
 * @file include/dashee/Log.h
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
#ifndef DASHEE_LOG_H_
#define DASHEE_LOG_H_

#include <iostream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

namespace dashee
{
    class Log;
}

// Define some index's which 
// represent the log level
#define LOG_INFO    0
#define LOG_WARNING 1
#define LOG_ERROR   2
#define LOG_FATAL   3

/**
 * Logging class.
 *
 * The log Header file, designed to be a singleton
 * Provides an interface for loggin to with using printf
 */
class dashee::Log
{

private:

    /**
     * The log status static array.
     *
     * Array of messages which hold.
     */
    static char logstatus[4][6];
    
    // Print the message given its message type
    static void print(const short int, const char *);

public:
    // Verbosity level can be shifted to hide debug messages
    static unsigned short int verbosity;
    
    // Print informational message
    static void info(const unsigned short int, const char *, ...);

    // Print infromational message given in std::string
    static void info(std::string, const unsigned short int = 1);

    // Print warning message
    static void warning(const unsigned short int, const char *, ...);

    // Print warning message given in std::string
    static void warning(std::string, const unsigned short int = 1);

    // Print error message
    static void error(const char *, ...);

    // Print warning error given in std::string
    static void error(std::string);

    // Print fatal message, and call exit(-1)
    static void fatal(const char *, ...);

    // Print fatal message given in string, and call exit(-1)
    static void fatal(std::string);

protected:
};

#endif
