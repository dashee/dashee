/**
 * @file include/dashee/Config.h
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

#ifndef DASHEE_CONFIG_H_
#define DASHEE_CONFIG_H_

#include <iostream>
#include <sstream>
#include <map>
#include <stack>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory>

#include <dashee/common.h>
#include <dashee/Log.h>
#include <dashee/Exception/Config.h>
#include <dashee/Exception/Invalid/Number.h>

namespace dashee
{
    class Config_Comparitor;
    class Config;
}

/**
 * The Config class.
 *
 * Class which holds configuration values in a map for easy access.
 * 
 * This config class, allows us to set config values, It also gives an 
 * interface, which allows us to get a value which is not set, by using a 
 * default parameter for get. Read more in the get functionality.
 *
 * When setting values, all previous values are overwritten, unless specified 
 * not to.
 *
 * All of our values are stored in char arrays. Conversions are done by helper 
 * functions defined by getType.
 *
 * Note if you ever use, set_uint, you **must call Config::cleanup, or
 * Initiate the Config object**, then the destructor will call the cleanup
 */
class dashee::Config
{
private:

protected:
    
    /**
     * The Config Comaprison class.
     *
     *  This is our comparitor class override, that is used by the multimap
     * to actually compare the values of char *, rather than just pointers
     */
    class Comparitor
    {
    public:

        //return true if 1st param matched character is less than its 2nd param
        bool operator()(const char * lhs, const char * rhs) const;
    };

 
    /** 
     * Map which holds all the configuration values.
     *
     * This will hold our, config values in key value pairs of characters.
     * All values are in character strings, so if a get is required
     * to be in a format use getType, where Type is the value. each type has do
     * defined in the function
     *
     * We choose a map as it gives us a quick an efficient way to get to our any
     * given key value
     *
     * Note because this is static, it has to initialized in Config.cpp
     */
    std::map<const char *, char *, Comparitor> configs;

    /**
     * Configure the loglevel globally for configuration.
     *
     * This function is sent to all Log::info() and Log::warning(), It is a 
     * handy way to turn the loging up, for just the config class, by default it
     * should be set to 5
     */
    int loglevel;
    
    // Checks to see if the character a valid key
    bool isValidKeyCharacter(const char * c);

    // Check if the key is valid
    bool isValidKey(const char * key);

public:
    
    // Initialize our log levels
    Config();

    // Set a given value, as string, int or 
    void set(const char *, const char *, const bool overwrite = true);
    void set(const char * key, const int value, const bool overwrite = true);
    void set(const char * key, const unsigned int value, const bool overwrite = true);
    void set(const char * key, const float value, const bool overwrite = true);
    
    // Get a given in the default format
    const char * get(const char * key, const char * defaultValue = NULL);

    // Get the value in a specific type, see return for type
    int getInt(const char * key, const int defaultValue = 0);
    unsigned int getUInt(const char * key, const unsigned int defaultValue = 0);
    float getFloat(const char * key, const float defaultValue = 0.0f);

    // Read values from a file
    void read(const char * filename);
    
    // A helpfull print function
    void print();

    // Get the size of the config map
    size_t size();
    
    // A helpfull print function
    void clear();

    // Deprecated
    void set_int(const char * key, const int value, const bool overwrite = true) 
        __attribute__((deprecated("Use set() instead")));
    void set_uint(const char * key, const unsigned int value, const bool overwrite = true) 
        __attribute__((deprecated("Use set() instead")));
    void set_float(const char * key, const float value, const bool overwrite = true) 
        __attribute__((deprecated("Use set() instead")));
    int get_int(const char * key, const int defaultValue = 0) 
        __attribute__((deprecated("Use getInt() instead")));
    unsigned int get_uint(const char * key, const unsigned int defaultValue = 0u) 
        __attribute__((deprecated("Use getUInt() instead")));
    float get_float(const char * key, const float defaultValue = 0.0f) 
        __attribute__((deprecated("Use getFloat() instead")));
    
    // Cleanup
    virtual ~Config();
};

#endif
