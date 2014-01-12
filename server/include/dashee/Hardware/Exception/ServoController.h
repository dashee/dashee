/**
 * @file include/dashee/Exception/ServoController.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_HARDWARE_EXCEPTION_SERVOCONTROLLER_H_
#define DASHEE_HARDWARE_EXCEPTION_SERVOCONTROLLER_H_

#include <dashee/Hardware/Exception.h>

namespace dashee
{
    namespace Hardware
    {
        class ExceptionServoController;
    }
}

class dashee::Hardware::ExceptionServoController
    : public dashee::Hardware::Exception
{
public:
    explicit ExceptionServoController() : Exception()
    {
    }
    explicit ExceptionServoController(const int ec) : Exception(ec)
    { 
    }
    explicit ExceptionServoController(std::string msg) : Exception(msg)
    { 
    }
};

#endif
