/**
 * Definition for the Common class.
 * 
 * @author Shahmir Javaid
 */

#include "Common.h"

/**
 * This function will Convert a string to a long int,
 * It follows exactly the strtol function in the standard,
 * except it throws an exception on invalid conversion
 *
 * @param string - The string to convert to number
 * @param base - The base of the string number
 *
 * @throws Exception_InvalidNumber - When @string is not a number
 *
 * returns long int - The converted value
 */
long int Common::strtol(const char * string, int base) 
{
    char * end;
    long int number = ::strtol(string, &end, base);
    
    if (end == string || *end != '\0' || errno == ERANGE)
    {
        char error[20];
        sprintf(error, "Number '%s' is invalid", string);
        throw Exception_InvalidNumber(error);
    }

    return number;
}
