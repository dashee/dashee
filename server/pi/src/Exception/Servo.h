#ifndef EXCEPTION_SERVO_H_
#define EXCEPTION_SERVO_H_

#include <dashee/Exception.h>

class Exception_Servo: public dashee::Exception
{
public:
    explicit Exception_Servo() : Exception()
    {
    }

    explicit Exception_Servo(const int ec) : Exception(ec)
    { 
    }
    explicit Exception_Servo(std::string msg) : Exception(msg)
    { 
    }
};

#endif
