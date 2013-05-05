/**
 * Define our static variables for the Config class. 
 * See Config.h for decleration
 * 
 * @author Shahmir Javaid
 */

#include "Config.h"

/** 
 * Initialize our maps, and internal variables
 */
Config::Config()
{
    loglevel = 5;
}

/** 
 * This function will set a value in our @configs map, the first parameter
 * represents the key value, the second represents the value to set, and the third
 * is a flag that will enable disable override of a key if present. The @override
 * key is by default set to 1 representing the variable will be overwritten
 *
 * The keys array needs to be deleted if it existed previously, this way the allocated memory
 * is being destroyed as its being used
 * 
 * @param (const char *) key - The key to set
 * @param (const char *) value - The value to set the key
 * @param (const unsigned short int) override - Should the existing value be overwritten
 */
void Config::set(const char * key, const char * value, const unsigned short int override)
{
    // Override is not allowed, and the key was found, so dont set
    // We only know the key is found, by seeing wheather the find iterator
    // is not on the end, os it must be pointing at a found element
    if (override == 0 && configs.find(key) != configs.end())
    {
        Log::info(loglevel+1, "Config::set Skipping '%s' Override not allowed", key, value);
        return;
    }
    
    // A previous, key exists. and we should delete the char array from memory
    // If threading, this requires locking. otherwise the world will blow up
    std::map<const char *, char *>::iterator dynamic_keys_it = dynamic_keys.find(key);
    if (dynamic_keys_it != dynamic_keys.end())
        delete [] dynamic_keys_it->second;
        
    // Set our value
    Log::info(loglevel+1, "Config::set %s, %s", key, value);
    configs[key] = (char *)value;
    Log::info(loglevel+4, "Config::set-get %s, %s", key, configs[key]);
}

/** 
 * This function is HACKEY, Given a int we need to convert it into a char *, and as our 
 * char * variable scope will only exist inside this function scope, we need to allocate
 * a pointer in memory. This has other problems. Altough our pointer is allocated in memory
 * we need to store this information in a keys array. Before reallocating the same key, 
 * we delete the previous found key using the keys array.
 *
 * The deleting is performed in the @set function. It will analyise wheather or not the
 * previous value needs to be deleted
 *
 * @param (const char *)key - The key to set
 * @param (const unsigned int)value - The integer to turn into a new char array
 * @param (const unsigned short int)override - Weather or not to leave the variable alone if 
 *  it is set
 */
void Config::set_uint(const char * key, const unsigned int value, const unsigned short int override)
{
    Log::info(loglevel+4, "Config::set_uint %s, %d", key, value);
    
    // Create a new buf, and send to Config::set
    // Also create and add new key value
    char * buf = new char[20];
    sprintf(buf, "%d", value);
    set(key, buf, override);

    //Now that we allocated, set our key
    dynamic_keys[key] = buf;

    return;
}

/** 
 * This will return a unsigne char * of the value from the @configs map in our class
 * The @defaultvalue set to NULL is returned if no key is found. 
 * 
 * @param (const char *)key - The key to look for
 * @param (const char *)defaultvalue - The default value to return if no key was found
 *
 * @return unsigned char * - The key value as found
 */
const char * Config::get(const char * key, const char * defaultvalue)
{
    if (configs.find(key) != configs.end())
    {
        Log::info(loglevel+1, "Config::get %s: %s", key, configs[key]);
        return configs[key];
    }
    
    Log::info(loglevel+1, "Config::get %s: default(%s)", key, defaultvalue);
    return defaultvalue;
}

/** 
 * Similar to the get function, except this deals in getting back a const unsigned int
 * 
 * @param 
 */
const unsigned int Config::get_uint(const char * key, const unsigned int defaultvalue)
{
    Log::info(loglevel+4, "Config::get_uint %s default(%d)", key, defaultvalue);
    
    //returns the value, in a buffer
    std::stringstream buf;
    buf << defaultvalue;

    //Converts a buffer to an int
    return strtol((char *)Config::get(key, buf.str().c_str()), (char **)NULL, 10);
}

/** 
 * Given a file name as a parameter, this function will read a config file
 * a config file holds key value pairs, seperated by the first space.
 * Each config line is broken by \n character and config files can have comments
 * these comments are defined by # character. Blank space are treated as empty.
 * Lines with only the key are treated as true
 *
 * This function will not throw any errors or return types. It will output log::warning(3)
 *
 * @param (const unsigned char*)file - The filename to load.
 */
void Config::read(const char * file)
{
}

/** 
 * This is a helpfull print function, which iterates the config values
 * and logs them
 */
void Config::print()
{
    for (
        std::map<const char *, char *>::iterator it=configs.begin();
        it != configs.end();
        ++it
    )
    {
        Log::info(loglevel, "Config[%s] %s", it->first, it->second);
    }
}

/**
 * This will delete the pointers, allocated in dynamic_keys. And also clear, the
 * maps
 */
void Config::cleanup()
{
    for (
        std::map<const char *, char *>::iterator it=dynamic_keys.begin();
        it != dynamic_keys.end();
        ++it
    )
    {
        delete it->second;
    }
    dynamic_keys.clear();
    configs.clear();
}

/**
 * Our destructor which only calls cleanup
 */
Config::~Config()
{
    Log::info(loglevel+5, "Deleting ~Config()");
    cleanup();
}
