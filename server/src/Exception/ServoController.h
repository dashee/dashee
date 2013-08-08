#ifndef EXCEPTION_SERVOCONTROLLER_H_
#define EXCEPTION_SERVOCONTROLLER_H_

#include <dashee/Exception.h>

class Exception_ServoController: public dashee::Exception
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
