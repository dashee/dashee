/**
 * The log Header file, designed to be a singleton
 * Provides an interface for loggin to with using printf
 *
 * @author Shahmir Javaid
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

class dashee::Log
{

private:
    // Array of messages which hold
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
