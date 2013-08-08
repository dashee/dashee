/**
 * A static class which provides Common functions which 
 * can be used throughout the program
 *
 * @author Shahmir Javaid
 */

#ifndef DASHEE_COMMON_H_
#define DASHEE_COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <dashee/Exception/InvalidNumber.h>

namespace dashee
{
    class Common;
}

class dashee::Common
{

private:
protected:
public:
    
    // string to long
    static long int strtol(const char *, const int = 10);

    // Check to see if a file exists given a path @param
    static bool fexists(const char *);
};

#endif
