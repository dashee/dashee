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
#include <syslog.h>

#include <dashee/Exception.h>

namespace dashee
{
    class Log;
}

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
    
    /**
     * File pointer to the out file.
     *
     * This is used by the log file to print to 
     * file
     */
    static FILE * fd;

    /**
     * The current type of log output.
     *
     * This holds the current type the log
     * is set to.
     */
    static int type;
    
    // Print the message given its message type
    static void print(int level, const char * message);

    // Print to a given stream
    static void printToStream(const int &level, const char * message);

    // print calls this
    static void printToSyslog(const int &level, const char * message);

    /**
     * Log levels which helps print
     * decide which way to go
     */
    enum levels
    {
        INFO,
        WARNING,
        ERROR,
        FATAL
    };

protected:


public:
    // Verbosity level can be shifted to hide debug messages
    static int verbosity;
    
    /**
     * types which describe the type
     * that logoutput will use
     */
    enum types
    {
        STDOUT,
        STDOUTONLY,
        SYSLOG,
        FILEWRITE,
        NOOUTPUT
    };

    // Close any pending logs
    static void close();

    // Open a FILE * stream
    static void openFile(const char * file);
    static void closeFile();

    // Open a syslog stream
    static void openSyslog(const char * identity, int facility);
    static void closeSyslog();
    
    // Print informational message
    static void info(const int, const char *, ...);
    static void info(std::string, const int = 1);

    // Print warning message
    static void warning(const int, const char *, ...);
    static void warning(std::string, const int = 1);

    // Print error message
    static void error(const char *, ...);
    static void error(std::string);

    // Print fatal message, and call exit(-1)
    static void fatal(const char *, ...);
    static void fatal(std::string);
};

#endif
