/**
 * @file include/dashee/Common.h
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

/**
 * Set of common functions
 * 
 * A static class which provides Common functions which 
 * can be used throughout the program
 */
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
