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
 * Cartesian coordinate.
 *
 * A simple class which encapsulates `[x, y, z]` Cartesian coordinates to be 
 * used by other classes.
 *
 * Usage:
 *
 *     dashee::Coordiante<int> p1(0,1,3);
 *     dashee::Coordinate<int> p2();
 *
 *     assert(p1 != p2);
 *
 *     p2.setY(2);
 *     dashee::Coordinate<int> p3 = p1+p2;
 *     assert(p3 == dashee::Coordinate<int>(0,3,3));
 */
template <class T> 
class dashee::Coordinate
{
protected:

    /**
     * X coordinate value.
     */
    T x;

    /**
     * Y coordinate value.
     */
    T y;

    /**
     * Z coordinate value.
     */
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

    Coordinate<T> operator+(const Coordinate<T> & rhs);
    Coordinate<T> operator-(const Coordinate<T> & rhs);

    virtual ~Coordinate();
};

#include <dashee/Coordinate.tpp>

#endif

