/**
 * @file include/dashee/Hardware/Exception/Servo.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_HARDWARE_EXCEPTION_SERVO_H_
#define DASHEE_HARDWARE_EXCEPTION_SERVO_H_

#include <dashee/Hardware/Exception.h>

namespace dashee
{
    namespace Hardware
    {
        class ExceptionServo;
    }
}

class dashee::Hardware::ExceptionServo: public dashee::Hardware::Exception
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
