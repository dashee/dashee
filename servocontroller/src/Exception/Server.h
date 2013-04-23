#ifndef EXCEPTION_SERVER_H
#define EXCEPTION_SERVER_H

#include <string.h>
#include <errno.h>
#include <stdexcept>

class Exception_Server: public std::runtime_error
{
    public:
        explicit Exception_Server() : runtime_error("Server Error")
        {
            this->ec = errno;
            this->message = strerror(this->ec);
        }
        explicit Exception_Server(const int ec) : runtime_error("Server Error") 
        { 
            this->message = "Server Error";
            this->ec = ec; 
        }
        explicit Exception_Server(const std::string msg) : runtime_error(msg) 
        {
            message = msg.c_str();    
        }

        virtual ~Exception_Server() throw(){}
        virtual const char* what()
        {
            return message;
        }
    protected:
        const char *message;
        unsigned short int ec;
};

#endif
