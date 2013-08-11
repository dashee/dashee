#ifndef DASHEE_EXCEPTION_GPIO_H_
#define DASHEE_EXCEPTION_GPIO_H_

#include <dashee/Exception.h>

namespace dashee
{
    class Exception_GPIO;
}

class dashee::Exception_GPIO: public dashee::Exception
{
public:
    explicit Exception_GPIO() : Exception()
    {
    }
    explicit Exception_GPIO(const int ec) : Exception(ec)
    { 
    }
    explicit Exception_GPIO(std::string msg) : Exception(msg)
    { 
    }
};

#endif
