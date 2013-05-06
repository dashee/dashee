/**
 * Define our static variables for the Config class. 
 * See Config.h for decleration
 * 
 * @author Shahmir Javaid
 */

#include "Config.h"

/** 
 * This will ensure when comparing our char * string in maps, that it compares
 * the actual value of the char * rather than its pointer position. 
 *
 * @param (const char *)lhs - Left hand side to be compared with the @rhs
 * @param (const char *)rhs - The right hand side to be compared against @lhs
 *
 * @return bool - true if the first character in lhs is less than the rhs counterpart
 */
bool Config_Comparitor::operator()(const char * lhs, const char * rhs) const
{
    int comparison = strcmp(lhs, rhs);
    if (comparison < 0) { return true; }
    return false;
}

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
 * Every time we set a new value, we delete the previous pointer
 * 
 * @param (const char *) key - The key to set
 * @param (const char *) value - The value to set the key
 * @param (const unsigned short int) override - Should the existing value be overwritten
 */
void Config::set(const char * key, const char * value, const unsigned short int override)
{
    // A previous, key exists. and we should delete the char array from memory
    // If threading, this requires locking. otherwise the world will blow up
    configs_it = configs.find(key);

    // Override is not allowed, and the key was found, so dont set
    // We only know the key is found, by seeing wheather the find iterator
    // is not on the end, os it must be pointing at a found element
    if (override == 0 && configs_it != configs.end())
    {
        Log::info(loglevel+1, "Config::set Skipping '%s' Override not allowed", key);
        return;
    }
    
    // Create a new space in memory, for our map to refer to
    char *pvalue = new char[strlen(value)+1];
    memcpy(pvalue, value, strlen(value)+1);
        
    // If we found a previous value delete the previous
    // And point to the new.
    if (configs_it != configs.end())
    {
        char * pointedkey = configs_it->second;
        configs_it->second = pvalue;
        delete [] pointedkey;

        // Set our value
        Log::info(loglevel+1, "Config::set %s, %s", key, pvalue);
    }
    
    // No previous key was found, so Create a new one
    else
    {
        // Create a new space in memory, for our map to refer to
        char *pkey = new char[strlen(key)+1];
        memcpy(pkey, key, strlen(key)+1);
        configs[pkey] = pvalue;

        Log::info(loglevel+1, "Config::set* %s, %s", pkey, pvalue);
    }
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
    char buf[20];
    sprintf(buf, "%d", value);
    set(key, buf, override);

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
    configs_it = configs.find((char *)key);
    if (configs_it != configs.end())
    {
        Log::info(loglevel+1, "Config::get %s: %s", key, configs_it->second);
        return configs_it->second;
    }
    
    Log::info(loglevel+1, "Config::get %s: default(%s)", key, defaultvalue);
    return defaultvalue;
}

/** 
 * Similar to the get function, except this deals in getting back a const unsigned int
 * 
 * @param (const char *)key - The key value to get
 * @param (const unsigned int)defaultvalue - The default values to return if none is found
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
    FILE * fd;
    fd = fopen(file, "r");
    
    // Problem with a file, not intrested, fall out gracefully
    if (fd == NULL) { return; }

    int c;
    do
    {
        c = fgetc(fd);
        //if (c == EOF) { break; }
        
        // The first character is a comment character;
        // Read till the end of line, and reset
        if (c == '#') 
        {
            // Keep going, till a next line is found
            while(c != '\n')
            {
                c = fgetc(fd);
                
                //There maybecases, where the config file ends with a comment
                // In this case break out
                if (c == EOF) { break; }
            }
        }
        
        // break out as we are at the end of file, no need to continue
        // As the only reason why we got to this one is that we were reading a comment
        // And it ended with the end of file
        if (c == EOF) 
            break; 
        
        // If we get a next line, continue, so the next iteration
        // Will pick up the slack
        if (c == '\n')
            continue;
        
        // Create a dynamic key, see below for cleanup comments
        char * key = new char[25];
        memset(key, 0, sizeof(key)); //Important, other wise the comparison goes wrong
        int keyN = 0;
        
        // Create a dynamic value, see below for cleanup comments
        char * value = new char[80];
        memset(value, 0, sizeof(value));
        int valueN = 0;
        
        // A variable that tells us wheather we are reading, 
        // a key or a value.
        bool iskey = true;

        // OK all the saftey checks for empty or comment lines
        // Are done, so we must be at a key value pair.
        while (c != '\n') 
        {   
            // If there is '=' character switch to value
            if (c == '=') { iskey = false; }
            
            // If iskey but there is a space, NOT allowed
            else if (iskey && c == ' ') { c = fgetc(fd); continue; }
            
            // If is key is not in the range of [a-zA-Z0-9]
            else if (
                iskey && 
                !(
                    (c >= 97 && c <= 122) || //a-z
                    (c >= 48 && c <= 57) || //0-9
                    (c >= 65 && c <= 90) //A-Z
                )
            ) { c = fgetc(fd); continue; }
            
            // Set our key
            if (iskey)
            {
                key[keyN] = c;
                keyN++;
            }
            //Set our value
            else
            {   
                // The starting value is garbage, overwrite it, by taking the pointer back
                // This will ensure left triming the string
                if (value[0] == ' ' || value[0] == '=') { valueN--; }
                value[valueN] = c;
                valueN++;
            }
            
            // Get the next character, Positioning of this
            // Must be at the end of the loop as we already have a character 
            // In our c value from the start of the read loop
            c = fgetc(fd);
        }

        // Only add the config, if the key is set, Note the clean up
        // of the set varibles are done by the destructor, this also the reason
        // Why we push our @key to our @dynamic_keys stack
        // Otherwise do some cleanup as we didnt use any arrays
        if (key[0] != 0)
            set(key, value);
        
        //Delete the keys, as they are being set in the set function
        delete [] key;
        delete [] value;

    } while (c != EOF);
}

/** 
 * This is a helpfull print function, which iterates the config values
 * and logs them
 */
void Config::print()
{
    for (
        configs_it=configs.begin();
        configs_it != configs.end();
        ++configs_it
    )
    {
        Log::info(loglevel, "Config[%s] %s", configs_it->first, configs_it->second);
    }
}

/**
 * This will delete the pointers, allocated in configs. And also clear, the
 * maps
 */
void Config::cleanup()
{
    for (
        configs_it=configs.begin();
        configs_it != configs.end();
        ++configs_it
    )
    {
        delete [] configs_it->first;
        delete [] configs_it->second;
    }
    
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
