/**
 * @file include/dashee/Threads/Exception.h
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

#ifndef DASHEE_THREADS_EXCEPTION_H_
#define DASHEE_THREADS_EXCEPTION_H_

#include <dashee/Exception.h>

namespace dashee
{
    namespace Threads
    {
        class Exception;
    }
}

class dashee::Threads::Exception: public dashee::Exception
{
public:
    explicit Exception() : dashee::Exception()
    {
    }
    explicit Exception(const int ec) : dashee::Exception(ec)
    { 
    }
    explicit Exception(std::string msg) : dashee::Exception(msg)
    { 
    }
};

#endif
