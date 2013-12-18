/**
 * @file include/dashee/Coordinate.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */
#ifndef DASHEE_COORDINATE_H_
#define DASHEE_COORDINATE_H_

#include <string.h>

namespace dashee
{
    template <class T> class Coordinate;
}

/**
 * Helpful class which pops the value as its read
 *
 * This class holds information about the current model state and also mixes
 * the values from the input
 */
template <class T> 
class dashee::Coordinate
{
protected:

    /**
     * The x, y and z values of the coordinates
     */
    T x;
    T y;
    T z;

public:
    // Construct and pass through to parent
    Coordinate();
    Coordinate(const T x, const T y, const T z);

    void setX(const T x);
    void setY(const T y);
    void setZ(const T z);

    T getX() const;
    T getY() const;
    T getZ() const;

    bool operator==(const Coordinate<T> & rhs) const;
    bool operator!=(const Coordinate<T> & rhs) const;

    virtual ~Coordinate();
};

#include <dashee/Coordinate.tpp>

#endif

