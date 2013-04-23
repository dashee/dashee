/* The log Header file, designed to be a singleton
 * Provides an interface for loggin to with printf
 *
 * @file        Log.h
 * @author      Shahmir Javaid
 * @copyright   Shahmir Javaid
 * @date        Sun Oct 28 2012
 */

#include <iostream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
//#include <stdarg.h>
#include <time.h>

#ifndef LOG_H
#define LOG_H

//Predefintions
#define LOG_INFO    0
#define LOG_WARNING 1
#define LOG_ERROR   2
#define LOG_FATAL   3

/* Log class is designed to be a singleton
 * which can be used to do provide a loggin 
 * interface
 */
class Log
{

private:
    //Static Character definition
    static char logstatus[4][6];
    
    //The print function, declerations
    static void print(const int, const char *);

public:
    static unsigned int verbosity;

    //Functions called by user
    static void info(const char *, const unsigned int = 1);
    static void info(std::string, const unsigned int = 1);
    static void warning(const char *, const unsigned int = 1);
    static void warning(std::string, const unsigned int = 1);
    static void error(const char *);
    static void error(std::string);
    static void fatal(const char *);
    static void fatal(std::string);

protected:

};

#endif
