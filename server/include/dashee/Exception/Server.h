/**
 * @file include/dashee/Exception/Server.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_EXCEPTION_SERVER_H_
#define DASHEE_EXCEPTION_SERVER_H_

#include <dashee/Exception.h>

namespace dashee
{
    class ExceptionServer;
}

class dashee::ExceptionServer: public dashee::Exception
{
public:
    explicit ExceptionServer() : Exception()
    {
    }
    explicit ExceptionServer(const int ec) : Exception(ec)
    { 
    }
    explicit ExceptionServer(std::string msg) : Exception(msg)
    { 
    }
};

#endif
