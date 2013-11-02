/**
 * @file include/dashee/common.h
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
 *                     you may distribute the resulting work only under a 
 *                     licence identical to this one.
 *
 * The terms and conditions are updated at http://dashee.co.uk/license. View the
 * project site for more details
 */

#ifndef DASHEE_COMMON_H_
#define DASHEE_COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

#include <sys/types.h>
#include <unistd.h>


#include <dashee/Config.h>
#include <dashee/Log.h>
#include <dashee/Exception/Invalid/Number.h>
#include <dashee/Exception/Invalid/Value.h>

namespace dashee
{

    // string to long
    long int strtol(const char * longString, const int base = 10);

    // int to string
    std::string itostr(int value);

    // Check to see if a file exists given a path @param
    bool fexists(const char * filename);

    // Map a value given from <from> to <to> ranges
    template<class T>
        void map(T *value, T fromLow, T fromHigh, T toLow, T toHigh);
    template<class T>
        T map(T value, T fromLow, T fromHigh, T toLow, T toHigh);

    // Constrain a given value between its min and max range
    template<class T>
        void constrain(T *value, T min, T max);
    template<class T>
        T constrain(T value, T min, T max);

};

#include <dashee/common.tpp>

#endif

