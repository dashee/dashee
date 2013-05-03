#include <string.h>
#include <errno.h>
#include <stdexcept>

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

class Exception: public std::runtime_error
{
    public:
        explicit Exception() : runtime_error("Exception")
        {
            this->ec = errno;
            this->message = strerror(this->ec);
        }
        explicit Exception(const int ec) : runtime_error("Exception") 
        { 
            this->message = "Exception";
            this->ec = ec; 
        }
        explicit Exception(const std::string msg) : runtime_error(msg) 
        {
            message = msg.c_str();    
        }

        virtual ~Exception() throw(){}
        virtual const char* what()
        {
            return message;
        }
    protected:
        const char *message;
        unsigned short int ec;
};

#endif
