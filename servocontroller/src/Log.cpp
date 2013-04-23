#include "Log.h"

void Log::print(const int x, const char *c) 
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    if (x > 3) { Log::fatal("No print type"); }

    printf(
        "%04u-%02u-%02u %02u:%02u:%02u %6s: %s\n", 
        (1900 + ltm->tm_year), 
        (1 + ltm->tm_mon), 
        (ltm->tm_mday), 
        (1 + ltm->tm_hour), 
        (1 + ltm->tm_min), 
        (1 + ltm->tm_sec), 
        logstatus[x], 
        c
    );
}

void Log::print(const int x, const std::string &c) 
{
    print(x, c.c_str());
}

void Log::info(const char *c, const unsigned int v)
{
    if (v <= verbosity)
    {
        Log::print(LOG_INFO, c);
    }
}

void Log::info(const std::string &c, const unsigned int v)
{
    info(c.c_str(), v);
}

void Log::warning(const char *c, const unsigned int v)
{
    if (v <= verbosity)
    {
        Log::print(LOG_WARNING, c);
    }
}

void Log::warning(const std::string &c, const unsigned int v)
{
    warning(c.c_str(), v);
}

void Log::error(const char *c) 
{ 
    Log::print(LOG_ERROR, c); 
}

void Log::error(const std::string &c) 
{ 
    error(c.c_str());
}

/* Fatal function is designed to run an exit
 * as well as a print
 * 
 * @param [const char *c] - The constant character to be printed
 *
 * @return void
 */
void Log::fatal(const char *c)
{
    Log::print(LOG_FATAL, c);
    exit(-1);
}

void Log::fatal(const std::string &c)
{
    fatal(c.c_str());
}

//Initialize our static variables
char Log::logstatus[4][6] = { 
    {'I', 'n', 'f', 'o', '\0', '\0'},
    {'W', 'a', 'r', 'n', '\0', '\0'},
    {'E', 'r', 'r', 'o', 'r', '\0'},
    {'F', 'a', 't', 'a', 'l', '\0'}
};

unsigned int Log::verbosity = 1;

