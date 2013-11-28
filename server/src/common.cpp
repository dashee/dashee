#include <dashee/common.h>

/**
 * Convert string to long.
 *
 * This function will Convert a string to a long int, It follows exactly the 
 * strtol function in the standard, except it throws an exception on invalid 
 * conversion
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
        throw ExceptionInvalidNumber(
                "dashee::strtol : Number '" + 
                (std::string)string + 
                "' is invalid"
            );

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
 * Convert a character to a string
 *
 * @param value The value to convert
 *
 * @returns the string value from the character
 */
std::string dashee::ctostr(char value)
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
 * Call usleep only if timeout is greater than 0
 *
 * @param timeout the Number of microseconds to timeoutfor
 */
void dashee::sleep(const unsigned int timeout)
{
    if (timeout == 0)
        return;

    usleep(timeout);
}

