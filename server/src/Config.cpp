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
 * @retval TRUE if the first character in `lhs` is less than the `rhs` 
 *         counterpart
 * @retval FALSE false if the first character in `lhs` is not less than `rhs`
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
 * Checks weather or the the given character is 
 * a valid key character.
 *
 * @param c reference to the character to look at
 *
 * @return boolean representing the character
 * @retval TRUE is valid character
 * @retval FALSE is invalid character
 */
bool Config::isValidKeyCharacter(const char * c)
{
    // Ensure the key is within the range
    if (
        *c == '-' || 
        *c == '_' ||
        (*c >= '0' && *c <= '9') ||
        (*c >= 'A' && *c <= 'Z') || 
        (*c >= 'a' && *c <= 'z') 
    )
        return true;

    return false;
}

/**
 * Checks weather or not the give key is valid.
 *
 * Check to ensuere:
 *   The key is not empty,
 *   starts with A-Za-z
 *   Go through each character and ensure that the character is in the valid set
 *    of characters allowed for a key
 *   Also ensure the key does not have double dashes or hyphens or mixture of 
 *    both
 *   Ensure the key does not end with '-' or '_'
 *
 * @param key The key c string
 *
 * @return boolean representing the validity
 * @retval FALSE is not a valid key
 * @retval TRUE is valid key
 */
bool Config::isValidKey(const char * const key)
{
    // Avoid empty to be the key
    if(*key == 0) 
        return false;
    
    // Ensure the key starts with A-Za-z
    if ((*key < 'A' && *key > 'Z') || (*key < 'a' || *key > 'z'))
        return false;

    const char * c = NULL;

    // Loop through and test
    for (c = key; *c != 0; c++)
    {
        if (!isValidKeyCharacter(c))
            return false;

        // Ensure we dont have '--' or '-_' or '__' in keys
        if ((*c == '-' || *c == '_') && *(c+1) != 0)
        {
            if (*(c+1) == '-' || *(c+1) == '_')
                return false;
        }
    }

    // Ensure the key does not end with dash
    if (c != NULL && (*(c-1) == '-' || *(c-1) == '_'))
        return false;

    return true;
}

/** 
 * Set a config value.
 *
 * This function will set a value in our Configs::configs map, the first 
 * parameter represents the key value, the second represents the value to set, 
 * and the third is a flag that will enable disable override of a key if 
 * present. The override key is by default set to 1 representing the variable 
 * will be overwritten.
 *
 * Every time we set a new value, we delete the previous pointer
 * 
 * @param key The key to set
 * @param value The value to set the key
 * @param overwrite Should the existing value be overwritten
 */
void Config::set(const char * key, const char * value, const bool overwrite)
{
    if(!isValidKey(key))
        throw ExceptionConfig("Key '" + (std::string)key + "' is invalid");

    // A previous, key exists and we should delete the char array from memory
    // If threading, this requires locking. Otherwise the world will blow up
    std::map<const char *, char *>::iterator it = this->configs.find(key);

    // Override is not allowed, and the key was found, so dont set
    // We only know the key is found, by seeing wheather the find iterator
    // is not on the end, os it must be pointing at a found element
    if (overwrite == 0 && it != this->configs.end())
        return;
    
    // Create a new space in memory, for our map to refer to
    char *pvalue = new char[strlen(value)+1];
    memcpy(pvalue, value, strlen(value)+1);
        
    // If we found a previous value delete the previous
    // And point to the new.
    if (it != this->configs.end())
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
        this->configs[pkey] = pvalue;
    }
}

/**
 * Set an integer config value.
 * 
 * @param key The key to set
 * @param value The int to turn into a new char array
 * @param overwrite Weather or not to leave the variable alone if it is set
 */
void Config::set(const char * key, const int value, const bool overwrite)
{
    // Create a new buf, and send to Config::set
    // Also create and add new key value
    char buf[20];
    sprintf(buf, "%d", value);
    set(key, buf, overwrite);
}

/**
 * Set an unsigned integer config value.
 *
 * @param key The key to set
 * @param value The integer to turn into a new char array
 * @param overwrite Weather or not to leave the variable alone if it is set
 */
void Config::set(
        const char * key, 
        const unsigned int value, 
        const bool overwrite
    )
{
    // Create a new buf, and send to Config::set
    // Also create and add new key value
    char buf[20];
    sprintf(buf, "%u", value);
    set(key, buf, overwrite);
}

/** 
 * Set a float config value.
 *
 * Same as Config::set_uint, except uses float in sprintf
 * 
 * @param key The key to set
 * @param value The float to turn into a new char array
 * @param overwrite Weather or not to leave the variable alone if it is set
 */
void Config::set(const char * key, const float value, const bool overwrite)
{
    // Create a new buf, and send to Config::set
    // Also create and add new key value
    char buf[30];
    sprintf(buf, "%f", value);
    set(key, buf, overwrite);
}

/**
 * Check if a value is set in our config
 *
 * @param key The key to check
 *
 * @retval TRUE the key is set
 * @retval FALSE the key is not set
 */
bool Config::isKeySet(const char * key)
{
    // A previous, key exists and we should delete the char array from memory
    // If threading, this requires locking. Otherwise the world will blow up
    std::map<const char *, char *>::iterator it = this->configs.find(key);

    return (it != this->configs.end());
}

/** 
 * Get a config value.
 *
 * This will return a unsigned char * of the value from the Config::configs map 
 * in our class The default value set to @p NULL is returned if no key is found.
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
 * Return the int value
 *
 * @param key The key value to get
 * @param defaultvalue The default values to return if none is found
 *
 * @returns The number if found, otherwise default
 *
 * @throws ExceptionConfig if ExceptionInvalidNumber is caught
 */
int Config::getInt(const char * key, const int defaultvalue)
{
    try
    {
        //returns the value, in a buffer
        std::stringstream buf;
        buf << defaultvalue;

        //Converts a buffer to an int
        return dashee::strtol((char *)Config::get(key, buf.str().c_str()));
    }
    catch (ExceptionInvalidNumber ex)
    {
        throw ExceptionConfig(
            "Config::get_int('" + 
            (std::string)key + 
            "') because the value was invalid"
        );
    }
}

/** 
 * Get an integer config value.
 * 
 * @param key The key value to get
 * @param defaultvalue The default values to return if none is found
 *
 * @returns The number if found, otherwise default
 * 
 * @throws ExceptionConfig if ExceptionInvalidNumber is caught
 */
unsigned int Config::getUInt(const char * key, const unsigned int defaultvalue)
{
    try
    {
        //returns the value, in a buffer
        std::stringstream buf;
        buf << defaultvalue;

        //Converts a buffer to an int
        return dashee::strtol((char *)Config::get(key, buf.str().c_str()));
    }
    catch (ExceptionInvalidNumber ex)
    {
        throw ExceptionConfig(
            "Config::get_uint('" + 
            (std::string)key + 
            "') because the value was invalid"
        );
    }
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
float Config::getFloat(const char * key, const float defaultvalue)
{
    //returns the value, in a buffer
    std::stringstream buf;
    buf << defaultvalue;

    //Converts a buffer to a float
    return strtof((char *)Config::get(key, buf.str().c_str()), (char **)NULL);
}

/**
 * Parse each line of the read configurations file
 *
 * @param fd The open file
 * @param key The array where the key is stored
 * @param value The array where the value is stored
 *
 * @returns boolean representing correct parsing
 */
bool Config::parseLine(FILE * fd, char * key, char * value)
{
    bool flag = false;

    if (parseKey(fd, key))
    {
        if (parseValue(fd, value))
        {
            flag = true;
        }
    }
            
    fseek(fd, -1, SEEK_CUR);

    // Check to see if the last value was next line, if not seek till it is
    //
    // We need to do this, because we don't know if the key was invalid or not, 
    // if the key was invalid, then we didn't bother reading the value and 
    // therefore our cursor is still left where it was to begin with. So we will
    // now seek to end of line or EOF
    for (signed char c = fgetc(fd); true; c = fgetc(fd))
    {
        if (c == '\n' || c == EOF)
            break;
    }

    return flag;
}

/**
 * Parse a key from file to the key param.
 *
 * @param fd The pointer to the open file
 * @param key The array of characters which holds the key value
 *
 * @retval TRUE Parsing went OK and key was set
 * @retval FALSE Parsing didn't go OK, so return fail
 */
bool Config::parseKey(FILE * fd, char * key)
{
    signed char c;
    size_t x = 0;

    while(true)
    {
        // No more room left for the key
        if (x == SIZE_KEY)
            return false;

        // Get the next character
        c = fgetc(fd);

        // Break out as the equal sign was found
        if (c == '=')
            break;

        // Handle left trim
        if (x == 0 && c == ' ')
            continue;
        
        // Dont do anything its a comment, or an empty line
        if (x == 0 && (c == '#' || c == '\n'))
            return false;

        // Handle right trim, by breaking
        // the loop further on will trim values
        if (x > 0 && c == ' ')
            break;

        if (x > 0 && (c == '\n' || c == EOF))
            return false;

        key[x++] = c;
    }

    // Right trim space, seek till '='
    if (x == 0)
        return false;

    // Loop through and seeking the character till we find a valid '=' 
    // representing the current key to be valid, other wise we find EOF, '\n' or
    // a non space, where non space suggests we have keys with spaces which is a
    // no go
    else if (x > 0 && c == ' ')
    {
        while(true)
        {
            c = fgetc(fd);

            // If found '=' break to return 
            if (c == '=')
                return true;

            // End of line found, this shoudnt be when we talk in context of 
            // keys
            else if (c == '\n' || c == EOF)
                return false;

            // We know the last character was a ' ' so if we are rtrimming we
            // should only get spaces, if not, we found another character so our
            // key is invalid and return false
            else if (c != ' ')
                return false;
        }
    }

    // This is a good catch, return true looks like a good key to me
    else if (x > 0 && c == '=')
    {
        return true;
    }

    // Invalid keys get to here, false because we want strict checking incase we
    // miss a few aspects
    return false;
}

/**
 * Parse the value
 * 
 * @param fd The pointer to the open file
 * @param value The array of characters which holds the value
 *
 * @retval TRUE Parsing went OK and key was set
 * @retval FALSE Parsing didn't go OK, so return fail
 */
bool Config::parseValue(FILE * fd, char * value)
{
    signed char c;
    size_t x = 0;
    signed char quote = 0;
    size_t lastCharacterPosition = 0;

    while (true)
    {
        c = fgetc(fd);

        // escape the next character by fetching the next character and only 
        // checking if we have reached the end of line, if not use the 
        // characters as is
        if (c == '\\')
        {
            c = fgetc(fd);

            if (c == EOF)
                break;
        }
        else
        {
            // No more room to store characters
            if (x == SIZE_VALUE)
                return false;

            if (c == '\n' || c == EOF)
                break;

            // Left Trim
            if (x == 0 && c == ' ')
                continue;

            // The value starts with " or '
            if (x == 0 && (c == '\"' || c == '\''))
            {
                quote = c;
                continue;
            }

            // The value has ended with " or '
            if (x > 0 && quote == c)
                break;

            // Store the position of the last space index value and keep the
            // same position, usefull for when we want to right trim
            if (c == ' ' && lastCharacterPosition == 0)
                lastCharacterPosition = x;
            else if (c != ' ')
                lastCharacterPosition = 0;
        }

        value[x++] = c;
    }

    if (x == 0)
        return false;

    // Right trim
    if (x > 0 && lastCharacterPosition != 0)
        value[lastCharacterPosition] = 0;

    // Make sure if we started with a quote we also ended with a quote, in the
    // case of `value"` this condition will trigger a return of false
    if (quote != 0 && c != quote)
        return false;
        
    return true;
}

/**
 * Read configuration from a file. 
 *
 * Given a file name as a parameter, this function will read a config file
 * a config file holds key value pairs, separated by the first space.
 * Each config line is broken by \n character and config files can have comments
 * these comments are defined by # character. Blank space are treated as empty.
 * Lines with only the key are treated as true
 *
 * This function will not throw any errors or return types. It will output 
 * log::warning(3)
 *
 * @param file The filename to load
 *
 * @throws ExceptionConfig If key is invalid
 */
void Config::read(const char * file)
{
    if (!fexists(file))
        return;

    FILE * fd;
    fd = fopen(file, "r");

    // Problem with a file, not interested, fall out gracefully
    if (fd == NULL) 
        return;

    // Go through each line and parse it
    for(int n = 1; true; n++)
    {
        char * key = new char[SIZE_KEY];
        memset(key, 0, sizeof(char)*SIZE_KEY);

        char * value = new char[SIZE_VALUE];
        memset(value, 0, sizeof(char)*SIZE_VALUE);

        try
        {
            if (parseLine(fd, key, value))
            {
                // Optamize the actual keys and set them to the size they 
                // actually are in memory.
                int keySize = strlen(key)+1;
                char *setKey = new char[keySize];
                memcpy(setKey, key, keySize);

                int valueSize = strlen(value)+1;
                char *setValue = new char[valueSize];
                memcpy(setValue, value, valueSize);

                set(setKey, setValue);
            }

            // This happens only when its a comment
            else if (*key != 0);

            else
                throw ExceptionConfig("Cannot parse");

        }
        catch (ExceptionConfig e)
        {
            dashee::Log::warning(
                    loglevel, 
                    "Line %d: %s", n, e.what()
                );
        }
        
        delete []key;
        delete []value;
         
        // Make sure that our loop breaks out when we have stopped reading the 
        // file. Otherwise seek back so our parser does not get confused
        if (fgetc(fd) == EOF)
            break;
        else
            fseek(fd, -1, SEEK_CUR);
    }
    
    fclose(fd);
}

/** 
 * Print a configuration.
 *
 * This is a helpful print function, which iterates the config values
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
 * Return the number of configurations set.
 *
 * A simple function which returns the size of the
 * current map
 *
 * @returns Number of config elements set
 */ 
size_t Config::size()
{
    return this->configs.size();
}   

/**
 * Clean up the configuration.
 *
 * This will delete the pointers, allocated in configs. And also clear, the
 * maps
 */
void Config::clear()
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
 * Our destructor which only calls clean-up
 */
Config::~Config()
{
    this->clear();
}
