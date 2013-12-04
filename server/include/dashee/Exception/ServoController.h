/**
 * @file include/dashee/Exception/ServoController.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_EXCEPTION_SERVOCONTROLLER_H_
#define DASHEE_EXCEPTION_SERVOCONTROLLER_H_

#include <dashee/Exception.h>

namespace dashee
{
    class ExceptionServoController;
}

class dashee::ExceptionServoController: public dashee::Exception
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
