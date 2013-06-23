#include "../Exception.h"

#ifndef EXCEPTION_INVALIDNUMBER_H_
#define EXCEPTION_INVALIDNUMBER_H_

class Exception_InvalidNumber: public Exception
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
