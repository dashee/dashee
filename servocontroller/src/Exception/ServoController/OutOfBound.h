#include "../ServoController.h"

#ifndef EXCEPTION_SERVERCONTROLLER_OUTOFBOUND_H_
#define EXCEPTION_SERVERCONTROLLER_OUTOFBOUND_H_

class Exception_ServoController_OutOfBound: public Exception_ServoController
{
public:
    explicit Exception_ServoController_OutOfBound() : Exception_ServoController()
    {
    }
    explicit Exception_ServoController_OutOfBound(const int ec) : Exception_ServoController(ec)
    { 
    }
    explicit Exception_ServoController_OutOfBound(std::string msg) : Exception_ServoController(msg)
    { 
    }
};

#endif
