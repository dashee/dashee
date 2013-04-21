#include <stdexcept>

class Exception_Servo: public std::runtime_error
{
    public:
        explicit Exception_Servo(const std::string msg) : runtime_error(msg) {};
        virtual ~Exception_Servo() throw(){}
        virtual const char* what() const throw()
        {
            return message.c_str();
        }
    protected:
        std::string message;
};
