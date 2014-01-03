/**
 * @file include/dashee/Point.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */
#ifndef DASHEE_POINT_H_
#define DASHEE_POINT_H_

#include <string.h>

namespace dashee
{
    template <class Coordinate> class Point;
}

/**
 * A Point with Coordinates
 *
 * A simple class which encapsulates `[x, y, z]` Cartesian coordinates in a 
 * Point to be used by other classes. The point here is represented in the 3D
 * space
 *
 * Usage:
 *
 *     dashee::Point<int> p1(0,1,3);
 *     dashee::Point<int> p2();
 *
 *     assert(p1 != p2);
 *
 *     p2.setY(2);
 *     dashee::Point<int> p3 = p1+p2;
 *     assert(p3 == dashee::Point<int>(0,3,3));
 */
template <class Coordinate> 
class dashee::Point
{
protected:

    /**
     * X coordinate value.
     */
    Coordinate x;

    /**
     * Y coordinate value.
     */
    Coordinate y;

    /**
     * Z coordinate value.
     */
    Coordinate z;

public:
    // Construct and pass through to parent
    Point();
    Point(const Coordinate x, const Coordinate y, const Coordinate z);

    void setX(const Coordinate x);
    void setY(const Coordinate y);
    void setZ(const Coordinate z);

    Coordinate getX() const;
    Coordinate getY() const;
    Coordinate getZ() const;

    bool operator==(const Point<Coordinate> & rhs) const;
    bool operator!=(const Point<Coordinate> & rhs) const;

    Point<Coordinate> operator+(const Point<Coordinate> & rhs);
    Point<Coordinate> operator-(const Point<Coordinate> & rhs);
    Point<Coordinate> operator*(const Coordinate & rhs);

    virtual ~Point();
};

#include <dashee/Point.tpp>

#endif
