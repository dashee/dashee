#include <dashee/common.h>

/**
 * Convert string to long.
 *
 * This function will Convert a string to a long int,
 * It follows exactly the strtol function in the standard,
 * except it throws an exception on invalid conversion
 *
 * @param string The string to convert to number
 * @param base The base of the string number
 *
 * @throws ExceptionInvalidNumber When `string` is not a number
 *
 * returns The converted value
 */
long int dashee::strtol(const char * string, const int base) 
{
    char * end;
    long int number = ::strtol(string, &end, base);
    
    if (end == string || *end != '\0' || errno == ERANGE)
    {
        char error[20];
        sprintf(error, "Number '%s' is invalid", string);
        throw ExceptionInvalidNumber(error);
    }

    return number;
}

/**
 * Convert int to string.
 *
 * @param value The value to convert
 *
 * @returns the value in a std::string
 */
std::string dashee::itostr(int value)
{
    std::stringstream ss;
    ss << value;
    std::string s(ss.str());
    return s;
}



/**
 * Check if file exists.
 *
 * This function will return true, if file exists.
 *
 * @param filename The name of the file
 *
 * @return Boolean to represent the file's existance
 * @retval TRUE File exists.
 * @retval FALSE Files does not exist.
 */
bool dashee::fexists(const char * filename) 
{
    struct stat buffer;   
    return (stat (filename, &buffer) == 0); 
}

/**
 * Create a pid file give by filepath.
 *
 * @param Create a pid file
 * @param Overwrite an existing pidfile (default to false)
 *
 * @retval false If file exists
 * @retval true if pid file was created
 */
bool dashee::createPID(const char * filepath, bool overwrite)
{
    if (dashee::fexists(filepath) && !overwrite)
        return false;

    FILE * fd = fopen(filepath, "w");
    
    if (fd == NULL)
        throw Exception("PID file '" + (std::string)filepath + "' could not opened for writing");

    // Write to file, close and return true;
    fprintf(fd, "%d\n", getpid());
    fclose(fd);
    return true;
}
