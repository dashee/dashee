/**
 * @file include/dashee/Vehicle/Multirotor/Quad/X.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */
#ifndef DASHEE_BUFFER_H_
#define DASHEE_BUFFER_H_

#include <queue>
#include <dashee/Exception/OutOfBounds.h>

namespace dashee
{
    template <class T> class Buffer;
}

/**
 * Helpfull class which pops the value as its read
 *
 * This class holds information about the current model state and also mixes
 * the values from the input
 */
template <class T> 
class dashee::Buffer : public std::queue<T>
{
protected:

public:
    // Construct and pass through to parent
    Buffer() : std::queue<T>() {}

    T next();

    virtual ~Buffer(){}
};

#include <dashee/Buffer.tpp>

#endif
