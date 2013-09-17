#include <dashee/Log.h>

using namespace dashee;

/**
 * Print log.
 *
 * This function takes a short int which represents the value
 * to be printed from the logstatus array. The value in the index
 * reprsents the error string type, We use an array as its easy to modify
 * We also ensure that the value of x is always below the size accessable for
 * logstatus. 
 * 
 * This function is also responsible for generating the date, If you want to change
 * the date format look here
 * 
 * The function takes the c argument which represents the message to print
 * 
 * @param errorStringIndex The logstatus string, accessed from the Log::logstatus array
 * @param message The character string to print
 */
void Log::print(const short int errorStringIndex, const char *message) 
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    if (errorStringIndex > 3) { Log::fatal("No print type"); }
    
    printf(
        "%04u-%02u-%02u %02u:%02u:%02u %6s: %s\n", 
        (1900 + ltm->tm_year), 
        (1 + ltm->tm_mon), 
        (ltm->tm_mday), 
        (1 + ltm->tm_hour), 
        (1 + ltm->tm_min), 
        (1 + ltm->tm_sec),
        logstatus[errorStringIndex], 
        message
    );
}

/**
 * Print informational log.
 *
 * This function takes in the verbosity level and checks it to be lower than Log::vebosity
 * this will determine wheather or not this function will print.
 * 
 * It then takes a char array which is the format of the 
 * string to print, followed by the ..., which represents a list of arguments which
 * are representd in c
 *
 * @param verbosity An identifier which represents wheater this message is printed
 * @param format The printf like format string
 * @param ... The va_args list of parameters for format string
 */
void Log::info(const unsigned short int verbosity, const char *format, ...)
{
    if (verbosity > Log::verbosity) { return; }
      
    char buffer[256];
    va_list args;
    va_start (args, format);
    vsprintf (buffer, format, args);
    Log::print(LOG_INFO, buffer);
    va_end (args);
}

/**
 * Print information log, given a string.
 *
 * This function is a helpfull std::string counterpart of the printf like
 * Log::info function, It also optionaly requires the verbosity level
 * by default verbosity is set to 1
 * 
 * @param message The message to print
 * @param verbosity The vebosity level check
 */
void Log::info(std::string message, const unsigned short int verbosity)
{
    info(message.c_str(), verbosity);
}

/**
 * Print a warning.
 *
 * This function takes in the verbosity level and checks it to be lower than Log::vebosity
 * this will determine wheather or not this function will print.
 * 
 * It then takes a char array which is the format of the 
 * string to print, followed by the ..., which represents a list of arguments which
 * are representd in format
 *
 * @param verbosity An identifier which represents wheater this message is printed
 * @param format The printf like format string
 * @param ... The va_args list of parameters for format string
 */
void Log::warning(const unsigned short int verbosity, const char *format, ...)
{
    if (verbosity > Log::verbosity) { return; }
      
    char buffer[256];
    va_list args;
    va_start (args, format);
    vsprintf (buffer, format, args);
    Log::print(LOG_WARNING, buffer);
    va_end (args);
}

/**
 * Print a warning, given a string.
 *
 * This function is a helpfull std::string counterpart of the printf like
 * Log::warning function, It also optionaly requires the verbosity level
 * by default verbosity is set to 1
 *
 * @param message The message to print
 * @param verbosity The vebosity level check
 */
void Log::warning(std::string message, const unsigned short int verbosity)
{
    warning(message.c_str(), verbosity);
}

/**
 * Print an error.
 *
 * This function takes a char array which is the format of the 
 * string to print, followed by the ..., which represents a list of arguments which
 * are representd in format
 *
 * @param format The printf like format string
 */
void Log::error(const char *format, ...) 
{ 
    char buffer[256];
    va_list args;
    va_start (args, format);
    vsprintf (buffer, format, args);
    Log::print(LOG_ERROR, buffer);
    va_end (args);
}

/**
 * Print an error, given a string.
 *
 * This function is a helpfull std::string counterpart of the printf like
 * Log::error function, It also optionaly requires the verbosity level
 * by default verbosity is set to 1
 * 
 * @param message The message to print
 */
void Log::error(std::string message) 
{ 
    Log::error(message.c_str()); 
}

/**
 * Print a fatal error.
 *
 * Unlike other messages in the log class, this one is specifically designed
 * to shut the program down by calling exit(-1) on the program.
 *
 * It takes the format string, and a va_args ... to print the printf like message
 * before it inevetably commits suicide. Marvin the fatal function
 *
 * @param format The printf like format string
 * @param ... The va_args list of parameters for format string
 */
void Log::fatal(const char *format, ...)
{
    char buffer[256];
    va_list args;
    va_start (args, format);
    vsprintf (buffer, format, args);
    Log::print(LOG_FATAL, buffer);
    va_end (args);
    exit(-1);
}

/**
 * Print a fatal error, given a string.
 *
 * This function is a helpfull std::string counterpart of the printf like
 * Log::fatal function, It also optionaly requires the verbosity level
 * by default verbosity is set to 1
 * 
 * @param message The message to print
 */
void Log::fatal(std::string message) 
{ 
    Log::fatal(message.c_str()); 
}

//Initialize our static variables
char Log::logstatus[4][6] = { 
    {'I', 'n', 'f', 'o', '\0', '\0'},
    {'W', 'a', 'r', 'n', '\0', '\0'},
    {'E', 'r', 'r', 'o', 'r', '\0'},
    {'F', 'a', 't', 'a', 'l', '\0'}
};

unsigned short int Log::verbosity = 1;
