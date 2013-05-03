#include "../Exception.h"

#ifndef EXCEPTION_SERVER_H_
#define EXCEPTION_SERVER_H_

class Exception_Server: public Exception
{
    public:
        explicit Exception_Server() : Exception()
        {
        }
        explicit Exception_Server(const int ec) : Exception(ec)
        { 
        }
        explicit Exception_Server(std::string msg) : Exception(msg)
        { 
        }
};

#endif
