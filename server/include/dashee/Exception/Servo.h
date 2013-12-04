/**
 * @file include/dashee/Exception/Servo.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_EXCEPTION_SERVO_H_
#define DASHEE_EXCEPTION_SERVO_H_

#include <dashee/Exception.h>

namespace dashee
{
    class ExceptionServo;
}

class dashee::ExceptionServo: public dashee::Exception
{
public:
    explicit ExceptionServo() : Exception()
    {
    }

    explicit ExceptionServo(const int ec) : Exception(ec)
    { 
    }
    explicit ExceptionServo(std::string msg) : Exception(msg)
    { 
    }
};

#endif
