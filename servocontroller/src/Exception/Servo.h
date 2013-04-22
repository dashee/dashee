#ifndef EXCEPTION_SERVO_H
#define EXCEPTION_SERVO_H

#include <stdexcept>

class Exception_Servo: public std::runtime_error
{
    public:
        explicit Exception_Servo() : runtime_error("Board Error")
        {
            this->ec = errno;
            this->message = strerror(this->ec);
        }
        explicit Exception_Servo(const int ec) : runtime_error("Board Error") 
        { 
            this->message = "Board Error";
            this->ec = ec; 
        }
        explicit Exception_Servo(const std::string msg) : runtime_error(msg) 
        {
            message = msg.c_str();    
        }

        virtual ~Exception_Servo() throw(){}
        virtual const char* what()
        {
            return message;
        }
    protected:
        const char *message;
        unsigned short int ec;
};

#endif
