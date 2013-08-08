#ifndef DASHEE_EXCEPTION_INVALIDNUMBER_H_
#define DASHEE_EXCEPTION_INVALIDNUMBER_H_

#include <dashee/Exception.h>

namespace dashee
{
    class Exception_InvalidNumber;
}

class dashee::Exception_InvalidNumber : public dashee::Exception
{
public:
    explicit Exception_InvalidNumber() : Exception()
    {
    }
    explicit Exception_InvalidNumber(const int ec) : Exception(ec)
    { 
    }
    explicit Exception_InvalidNumber(std::string msg) : Exception(msg)
    { 
    }
};

#endif
