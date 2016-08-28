/**
 * @file include/dashee/Exception/Vehicle.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_EXCEPTION_MODEL_H_
#define DASHEE_EXCEPTION_MODEL_H_

#include <dashee/Exception.h>

namespace dashee
{
    class ExceptionVehicle;
}

class dashee::ExceptionVehicle: public dashee::Exception
{
public:
    explicit ExceptionVehicle() : Exception()
    {
    }
    explicit ExceptionVehicle(const int ec) : Exception(ec)
    { 
    }
    explicit ExceptionVehicle(std::string msg) : Exception(msg)
    { 
    }
};

#endif
