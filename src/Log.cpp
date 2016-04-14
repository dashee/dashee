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
 * @param level The logstatus string level, accessed from the Log::logstatus array
 * @param message The character string to print
 */
void Log::print(const int level, const char *message) 
{
    // Switch the type value and do the write accordingly
    switch (type)
    {
        case STDOUT:
        case STDOUTONLY:
        case FILEWRITE:
            Log::printToStream(level, message);
            break;
        case SYSLOG:
            Log::printToSyslog(level, message);
            break;
        case NOOUTPUT:
        default:
            break;
    }
}

/**
 * Print to stream.
 *
 * Simple function which adds the date and time, before printing
 * to the appropriate stream, note in STDOUT mode, errors are sent
 * to std::stderr, In filemode, the filetype pointer points to an open
 * file
 *
 * @param level The level of the log
 * @param message The message to log
 *
 * @throws Exception if type is FILEWRITE and fd is still NULL
 */
void Log::printToStream(const int &level, const char * message)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    // Throw an exception if fd is not initiated
    if (type == FILEWRITE && fd == NULL)
        throw dashee::Exception("You must open fd in Log before writing to file");

    // If the type is set to STDOUT, then errors or fatal
    // messages should go to stderr
    FILE * filetype;
    if (type == FILEWRITE)
        filetype = fd;
    else if (type == STDOUT && level > 1)
        filetype = stderr;
    else
        filetype = stdout;

    if (level > 3) { Log::fatal("No print type"); }
  
    fprintf(
        filetype,
        "%04u-%02u-%02u %02u:%02u:%02u %6s: %s\n", 
        (1900 + ltm->tm_year), 
        (1 + ltm->tm_mon), 
        (ltm->tm_mday), 
        (1 + ltm->tm_hour), 
        (1 + ltm->tm_min), 
        (1 + ltm->tm_sec),
        logstatus[level], 
        message
    );
    fflush(filetype);
}

/**
 * Log to syslog.
 *
 * First convert the Log priority to syslog
 * priority, then print to syslog
 */
void Log::printToSyslog(const int &level, const char * message)
{
    int priority;

    switch(level)
    {
        case Log::INFO:
            priority = LOG_NOTICE;
            break;
        case Log::WARNING:
            priority = LOG_WARNING;
            break;
        case Log::ERROR:
            priority = LOG_ERR;
            break;
        case Log::FATAL:
            priority = LOG_CRIT;
            break;
        default:
            priority = LOG_NOTICE;
            break;
    }

    syslog(priority, "%s", message);
}

/**
 * Close pending logs.
 *
 * Closes any pending logs, which open*() function
 * may interupt with
 */
void Log::close()
{
    if (Log::type == FILEWRITE)
        Log::closeFile();
    else if (Log::type == SYSLOG)
        Log::closeSyslog();
}

/**
 * Opens a file and sets fd
 *
 * @param file The string containing the filepath
 *
 * @throws Exception If fileopening failed
 */
void Log::openFile(const char * file)
{
    Log::close();

    fd = fopen(file, "a+");
    if (fd == NULL)
        throw dashee::Exception("Opening file failed in  Log::openFile");

    Log::type = FILEWRITE;
}

/**
 * Close the open fd.
 */
void Log::closeFile()
{
    if (fd != NULL)
        fclose(fd);
}

/**
 * Open syslog.
 *
 * @param identity the identity of the log messages which will
 *                 be logged by syslog
 * @param facility the facility to set the openlog to
 */
void Log::openSyslog(const char * identity, int facility)
{
    Log::close();

    openlog(identity, LOG_PID, facility);
    type = Log::SYSLOG;
}

/**
 * Close syslog.
 */
void Log::closeSyslog()
{
    closelog();
    type = Log::STDOUT;
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
void Log::info(const int verbosity, const char *format, ...)
{
    if (verbosity > Log::verbosity) { return; }
      
    char buffer[256];
    va_list args;
    va_start (args, format);
    vsprintf (buffer, format, args);
    Log::print(Log::INFO, buffer);
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
void Log::info(std::string message, const int verbosity)
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
void Log::warning(const int verbosity, const char *format, ...)
{
    if (verbosity > Log::verbosity) { return; }
      
    char buffer[256];
    va_list args;
    va_start (args, format);
    vsprintf (buffer, format, args);
    Log::print(Log::WARNING, buffer);
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
void Log::warning(std::string message, const int verbosity)
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
    Log::print(Log::ERROR, buffer);
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
    Log::print(Log::FATAL, buffer);
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

// Initialize our static variables
char Log::logstatus[4][6] = { 
    {'I', 'n', 'f', 'o', '\0', '\0'},
    {'W', 'a', 'r', 'n', '\0', '\0'},
    {'E', 'r', 'r', 'o', 'r', '\0'},
    {'F', 'a', 't', 'a', 'l', '\0'}
};

// Set default verbosity
int Log::verbosity = 1;

// Set the default output type
int Log::type = Log::STDOUT;

// Default the fd value
FILE * Log::fd = NULL;
