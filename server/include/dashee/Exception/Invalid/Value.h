/**
 * @file include/dashee/Exception/Invalid/Value.h
 * @author Shahmir Javaid
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. In general
 * you are free to copy, distribute, display, and perform the work, 
 * you are also free to make derivative works, under the following conditions:
 *  - Attribution    — You must give dashee's author credit.
 *  - Non-Commercial - You may not use this dashee for commercial 
 *                     purposes without permission.
 *  - Share Alike    — If you alter, transform, or build upon this work, 
 *                     you may distribute the resulting work only under a 
 *                     licence identical to this one.
 *
 * The terms and conditions are updated at http://dashee.co.uk/license. View the
 * project site for more details
 */

#ifndef DASHEE_EXCEPTION_INVALID_VALUE_H_
#define DASHEE_EXCEPTION_INVALID_VALUE_H_

#include <dashee/Exception.h>

namespace dashee
{
    class ExceptionInvalidValue;
}

class dashee::ExceptionInvalidValue : public dashee::ExceptionInvalid
{
public:
    explicit ExceptionInvalidValue() : ExceptionInvalid()
    {
    }
    explicit ExceptionInvalidValue(const int ec) : ExceptionInvalid(ec)
    { 
    }
    explicit ExceptionInvalidValue(std::string msg) : ExceptionInvalid(msg)
    { 
    }
};

#endif
