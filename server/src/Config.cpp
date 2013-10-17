#include <dashee/Config.h>

using namespace dashee;

/** 
 * Compare lhs vs rhs.
 *
 * This will ensure when comparing our char * string in maps, that it compares
 * the actual value of the char * rather than its pointer position. 
 *
 * @param lhs Left hand side to be compared with the `rhs`
 * @param rhs The right hand side to be compared against `lhs`
 *
 * @returns A boolean value depending on the weight of `lhs` vs `rhs`
 * @retval TRUE if the first character in `lhs` is less than the `rhs` counterpart
 * @retval FALSE false if the firstcharacter in `lhs` is not less than `rhs`
 */
bool Config::Comparitor::operator()(const char * lhs, const char * rhs) const
{
    int comparison = strcmp(lhs, rhs);
    if (comparison < 0) 
        return true;
    return false;
}

/** 
 * Construct.
 *
 * Initialize our maps, and internal variables
 */
Config::Config()
{
    loglevel = 5;
}

/** 
 * Set a config value.
 *
 * This function will set a value in our Configs::configs map, the first parameter
 * represents the key value, the second represents the value to set, and the third
 * is a flag that will enable disable override of a key if present. The override
 * key is by default set to 1 representing the variable will be overwritten
 *
 * Every time we set a new value, we delete the previous pointer
 * 
 * @param key The key to set
 * @param value The value to set the key
 * @param override Should the existing value be overwritten
 */
void Config::set(const char * key, const char * value, const unsigned short int override)
{
    // A previous, key exists. and we should delete the char array from memory
    // If threading, this requires locking. otherwise the world will blow up
    std::map<const char *, char *>::iterator it = configs.find(key);

    // Override is not allowed, and the key was found, so dont set
    // We only know the key is found, by seeing wheather the find iterator
    // is not on the end, os it must be pointing at a found element
    if (override == 0 && it != configs.end())
        return;
    
    // Create a new space in memory, for our map to refer to
    char *pvalue = new char[strlen(value)+1];
    memcpy(pvalue, value, strlen(value)+1);
        
    // If we found a previous value delete the previous
    // And point to the new.
    if (it != configs.end())
    {
        char * pointedkey = it->second;
        it->second = pvalue;
        delete [] pointedkey;
    }
    
    // No previous key was found, so Create a new one
    else
    {
        // Create a new space in memory, for our map to refer to
        char *pkey = new char[strlen(key)+1];
        memcpy(pkey, key, strlen(key)+1);
        configs[pkey] = pvalue;
    }
}

/**
 * Set an integer config value.
 *
 * This function is HACKEY, Given a int we need to convert it into a char *, and as our 
 * char * variable scope will only exist inside this function scope, we need to allocate
 * a pointer in memory. This has other problems. Altough our pointer is allocated in memory
 * we need to store this information in a keys array. Before reallocating the same key, 
 * we delete the previous found key using the keys array.
 *
 * The deleting is performed in the Config::set function. It will analyise wheather or not the
 * previous value needs to be deleted
 *
 * @param key The key to set
 * @param value The integer to turn into a new char array
 * @param override Weather or not to leave the variable alone if it is set
 */
void Config::set_uint(const char * key, const unsigned int value, const unsigned short int override)
{
    // Create a new buf, and send to Config::set
    // Also create and add new key value
    char buf[20];
    sprintf(buf, "%d", value);
    set(key, buf, override);

    return;
}

/** 
 * Set a float config value.
 *
 * Same as Config::set_uint, except uses float in sprintf
 * 
 * @param key The key to set
 * @param value The float to turn into a new char array
 * @param override Weather or not to leave the variable alone if it is set
 */
void Config::set_float(const char * key, const float value, const unsigned short int override)
{
    // Create a new buf, and send to Config::set
    // Also create and add new key value
    char buf[20];
    sprintf(buf, "%f", value);
    set(key, buf, override);

    return;
}

/** 
 * Get a config value.
 *
 * This will return a unsigne char * of the value from the Config::configs map in our class
 * The default value set to @p NULL is returned if no key is found. 
 * 
 * @param key The key to look for
 * @param defaultvalue The default value to return if no key was found
 *
 * @returns The key value as found, otherwise default
 */
const char * Config::get(const char * key, const char * defaultvalue)
{
    std::map<const char *, char *>::iterator it = configs.find((char *)key);

    if (it != configs.end())
        return it->second;
    
    return defaultvalue;
}

/** 
 * Get an integer config value.
 *
 * Similar to the get function, except this deals in getting back a const unsigned int
 * 
 * @param key The key value to get
 * @param defaultvalue The default values to return if none is found
 *
 * @returns The number if found, otherwise default
 */
const unsigned int Config::get_uint(const char * key, const unsigned int defaultvalue)
{
    //returns the value, in a buffer
    std::stringstream buf;
    buf << defaultvalue;

    //Converts a buffer to an int
    return strtol((char *)Config::get(key, buf.str().c_str()));
}

/** 
 * Get a float config value.
 *
 * Similar to the Config::get_uint, except deals in float
 * 
 * @param key The key value to get
 * @param defaultvalue The default values to return if none is found
 *
 * @returns The number if found, otherwise default
 */
const float Config::get_float(const char * key, const float defaultvalue)
{
    //returns the value, in a buffer
    std::stringstream buf;
    buf << defaultvalue;

    //Converts a buffer to a float
    return strtof((char *)Config::get(key, buf.str().c_str()), (char **)NULL);
}

/**
 * Read configuration from a file. 
 *
 * Given a file name as a parameter, this function will read a config file
 * a config file holds key value pairs, seperated by the first space.
 * Each config line is broken by \n character and config files can have comments
 * these comments are defined by # character. Blank space are treated as empty.
 * Lines with only the key are treated as true
 *
 * This function will not throw any errors or return types. It will output log::warning(3)
 *
 * @param file The filename to load.
 */
void Config::read(const char * file)
{
    if (!fexists(file))
        return;

    FILE * fd;
    fd = fopen(file, "r");

    // Problem with a file, not intrested, fall out gracefully
    if (fd == NULL) 
        return;

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
                if (c == EOF) 
                    break;
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
        char * key = new char[40];
        memset(key, 0, sizeof(char)*25); //Important, other wise the comparison goes wrong
        int keyN = 0;
        
        // Create a dynamic value, see below for cleanup comments
        char * value = new char[80];
        memset(value, 0, sizeof(char)*80);
        int valueN = 0;
        int valueTrim = 0;
        
        // A variable that tells us wheather we are reading, 
        // a key or a value.
        bool iskey = true;

        // OK all the saftey checks for empty or comment lines
        // Are done, so we must be at a key value pair.
        while (c != '\n')
        {   
            // If there is '=' character switch to value
            if (iskey && c == '=') { iskey = false; }
            
            // If iskey but there is a space, NOT allowed
            else if (iskey && c == ' ') { c = fgetc(fd); continue; }
            
            // If is key is not in the range of [a-zA-Z0-9]
            else if (
                iskey && 
                (
                    (c >= 97 && c <= 122) || //a-z
                    (c >= 48 && c <= 57) || //0-9
                    (c >= 65 && c <= 90) || //A-Z
                    (c == '-')
                )
            ) 
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
                
                // valueTrim will hold the last position, which held
                // a character other than ' ', This number + 1 should be
                // set to 0 to rtrim the char array.
                if (c != ' ') { valueTrim=valueN; }
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
        {
            value[valueTrim] = 0; // Trim our value
            set(key, value);
        }
        
        //Delete the keys, as they are being set in the set function
        delete [] key;
        delete [] value;

    } while (c != EOF);
    
    fclose(fd);
}

/** 
 * Print a configuration.
 *
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
        dashee::Log::info(loglevel, "Config[%s] %s", it->first, it->second);
    }
}

/**
 * Clean up the configuration.
 *
 * This will delete the pointers, allocated in configs. And also clear, the
 * maps
 */
void Config::cleanup()
{
    for (
        std::map<const char *, char *>::iterator it=configs.begin();
        it != configs.end();
        ++it
    )
    {
        delete [] it->first;
        delete [] it->second;
    }
    
    configs.clear();
}

/**
 * Destructor.
 *
 * Our destructor which only calls cleanup
 */
Config::~Config()
{
    cleanup();
}
