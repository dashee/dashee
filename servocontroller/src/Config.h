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
    static std::map<const char *, char *> configs;
    
    /** 
     * HACK, READ THIS
     * Due to the limitation of integers being converted to char[] that only
     * exist inside there called scope. we use memory allocation for this.
     * Because the map does its own cleanup, we are only intereseted in storing
     * those keys that the configs map will not delete.
     * 
     * So we create this map, which holds all the keys in the configs that are dynamic
     */
    static std::map<const char *, char *> dynamic_keys;

public:
    
    /**
     * This function is sent to all log::info and log::waring, It is a handy way
     * to turn the loging up, for just the config class, by default it should be set to
     * 5
     */
    static int loglevel;
    
    Config() {  }

    // Set a given value
    static void set(const char *, const char *, const unsigned short int = 1);

    // Set a given value
    static void set_uint(const char *, const unsigned int, const unsigned short int = 1);
    
    // Get a given value
    static const char * get(const char *, const char * = NULL);
    
    // Get a given value
    static const unsigned int get_uint(const char *, const unsigned int = 0);

    // Read values from a file
    static void read(const char *);
    
    // A helpfull print function
    static void print();
    
    // A helpfull print function
    static void cleanup();
    
    // Cleanup
    ~Config();
};

//Config::configs = std::maps<const unsigned char *, const unsgined char *>;

#endif
