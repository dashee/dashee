#include "../Exception.h"

#ifndef EXCEPTION_SERVOCONTROLLER_H_
#define EXCEPTION_SERVOCONTROLLER_H_

class Exception_ServoController: public Exception
{
public:
    explicit Exception_ServoController() : Exception()
    {
    }
    explicit Exception_ServoController(const int ec) : Exception(ec)
    { 
    }
    explicit Exception_ServoController(std::string msg) : Exception(msg)
    { 
    }
};

#endif
