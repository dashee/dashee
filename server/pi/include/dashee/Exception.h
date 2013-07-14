
#ifndef DASHEE_EXCEPTION_H_
#define DASHEE_EXCEPTION_H_

#include <string.h>
#include <errno.h>
#include <stdexcept>

namespace dashee
{
    class Exception;
}

class dashee::Exception: public std::runtime_error
{

protected:
    
    /** 
     * The message of the exception, by default set to
     * "Exception"
     */
    const char *message;

    /** 
     * The error code to set, by default set to errno
     */
    unsigned short int ec;

public:

    // An empty exception
    explicit Exception() : runtime_error("Exception")
    {
        this->ec = errno;
        this->message = strerror(this->ec);
    }

    // An exception when only the error code is given
    explicit Exception(const int ec) : runtime_error("Exception") 
    { 
        this->message = "Exception";
        this->ec = ec; 
    }

    // An exception where the message is given
    explicit Exception(const std::string msg) : runtime_error(msg) 
    {
        this->ec = errno;
        this->message = msg.c_str();
    }
    
    // So the exception can be overwritten
    virtual ~Exception() throw(){}

    // Returns the message
    virtual const char* what()
    {
        return message;
    }

};

#endif
