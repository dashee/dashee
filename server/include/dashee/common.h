/**
 * @file include/dashee/common.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
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

    // char to string
    std::string ctostr(char value);

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

    // Helpfull function to encapsulate usleep so 0 usleep is not run
    void sleep(const unsigned int timeout);
};

#include <dashee/common.tpp>

#endif

