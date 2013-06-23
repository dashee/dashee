#include "../Exception.h"

#ifndef EXCEPTION_CONFIG_H_
#define EXCEPTION_CONFIG_H_

class Exception_Config: public Exception
{
public:
    explicit Exception_Config() : Exception()
    {
    }
    explicit Exception_Config(const int ec) : Exception(ec)
    { 
    }
    explicit Exception_Config(std::string msg) : Exception(msg)
    { 
    }
};

#endif
