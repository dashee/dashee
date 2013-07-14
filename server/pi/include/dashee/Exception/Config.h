#ifndef DASHEE_EXCEPTION_CONFIG_H_
#define DASHEE_EXCEPTION_CONFIG_H_

#include <dashee/Exception.h>

namespace dashee
{
    class Exception_Config;
}

class dashee::Exception_Config: public dashee::Exception
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
