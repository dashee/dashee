/**
 * This config files, allows us to set config values, It also gives an interface,
 * which allows us to get a value which is not set, by using a default parameter
 * for get. Read more in the get functionality.
 *
 * When setting values, all previous values are overwritten, unless specified not to.
 *
 * All of our values are stored in char arrays. Conversions are done by helper functions
 * defined by getType.
 *
 * Note if you ever use, set_uint, you MUST MUST MUST call Config::cleanup, or
 * Initiate the Config object, then the destructor will call the cleanup
 *
 * @author Shahmir Javaid
 */

#include <iostream>
#include <sstream>
#include <map>
#include <stack>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Log.h"
#include <memory>

#ifndef CONFIG_H_
#define CONFIG_H_

class Config
{
private:
 
    /** 
     * This will hold our, config values in key value pairs of characters.
     * All values are in character strings, so if a get is required
     * to be in a format use getType, where Type is the value. each type has do
     * defined in the function
     *
     * We choose a map as it gives us a quick an efficient way to get to our any given
     * key value
     *
     * Note because this is static, it has to initialized in Config.cpp
     */
    std::map<const char *, char *> configs;

    std::map<const char *, char *>::iterator configs_it;

    std::stack<const char *> dynamic_keys;

    /**
     * This function is sent to all log::info and log::waring, It is a handy way
     * to turn the loging up, for just the config class, by default it should be set to
     * 5
     */
    int loglevel;

public:
    
    // Initialize our log levels
    Config();

    // Set a given value
    void set(const char *, const char *, const unsigned short int = 1);

    // Set a given value
    void set_uint(const char *, const unsigned int, const unsigned short int = 1);
    
    // Get a given value
    const char * get(const char *, const char * = NULL);
    
    // Get a given value
    const unsigned int get_uint(const char *, const unsigned int = 0);

    // Read values from a file
    void read(const char *);
    
    // A helpfull print function
    void print();
    
    // A helpfull print function
    void cleanup();
    
    // Cleanup
    ~Config();
};

//Config::configs = std::maps<const unsigned char *, const unsgined char *>;

#endif
