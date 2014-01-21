/**
 * @file include/dashee/Point.tpp
 * @author Shahmir Javaid
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_POINT_TPP_
#define DASHEE_POINT_TPP_

/**
 * Do nothing constructor, rely the constructor of T
 * to default X, Y and Z
 */
template <class Coordinate> dashee::Point<Coordinate>::Point()
    : x(Coordinate()), y(Coordinate()), z(Coordinate())
{
}

/**
 * Create a Point from one value.
 *
 * @param value The value to use to create a point
 */
template <class Coordinate> dashee::Point<Coordinate>::Point(
        const Coordinate value
    )
{
    this->setX(value);
    this->setY(value);
    this->setZ(value);
}

/**
 * Set the value of the coordinates from the outset of the construction
 *
 * @param x The value of X
 * @param y The value of Y
 * @param z The value of Z
 */
template <class Coordinate> dashee::Point<Coordinate>::Point(
	const Coordinate x, 
	const Coordinate y, 
	const Coordinate z
    )
{
    this->setX(x);
    this->setY(y);
    this->setZ(z);
}

/**
 * Set the value of X
 *
 * @param x the value to set
 */
template <class Coordinate> 
void dashee::Point<Coordinate>::setX(const Coordinate x)
{
    this->x = x;
}

/**
 * Set the value of Y
 *
 * @param y the value to set
 */
template <class Coordinate> 
void dashee::Point<Coordinate>::setY(const Coordinate y)
{
    this->y = y;
}

/**
 * Set the value of Z
 *
 * @param z the value to set
 */
template <class Coordinate> 
void dashee::Point<Coordinate>::setZ(const Coordinate z)
{
    this->z = z;
}

/**
 * Return the value of X
 *
 * @returns value of x
 */
template <class Coordinate> Coordinate dashee::Point<Coordinate>::getX() const
{
    return x;
}

/**
 * Return the value of Y
 *
 * @returns value of y
 */
template <class Coordinate> Coordinate dashee::Point<Coordinate>::getY() const
{
    return y;
}

/**
 * Return the value of Z
 *
 * @returns value of z
 */
template <class Coordinate> Coordinate dashee::Point<Coordinate>::getZ() const
{
    return z;
}

/**
 * Operator which tests the equality of two coordinates.
 *
 * @param rhs The right hand side to test against
 */
template <class Coordinate> 
bool dashee::Point<Coordinate>::operator ==(
	const dashee::Point<Coordinate>& rhs
    ) const
{
    return 
	this->x == rhs.getX() && 
	this->y == rhs.getY() && 
	this->z == rhs.getZ();
}

/**
 * Operator which tests the non-equality of two coordinates.
 *
 * @param rhs The right hand side to test against
 */
template <class Coordinate> 
bool dashee::Point<Coordinate>::operator !=(
	const dashee::Point<Coordinate>& rhs
    ) const
{
    return 
	this->x != rhs.getX() ||
	this->y != rhs.getY() ||
	this->z != rhs.getZ();
}
/**
 * Multiply the value of Coordinate to all the coordinates of the point.
 *
 * @param rhs The value to multiply all coordinates by
 *
 * @returns itself as the changed value
 */
template <class Coordinate>
dashee::Point<Coordinate> & dashee::Point<Coordinate>::operator*=(
	const Coordinate & rhs
    )
{
    this->setX(this->getX() * rhs);
    this->setY(this->getY() * rhs);
    this->setZ(this->getZ() * rhs);

    return *this;
}

/**
 * Do nothing destruct
 */
template <class Coordinate> dashee::Point<Coordinate>::~Point()
{

}

/**
 * Add the values of the left hand side to the right hand side
 *
 * @param lhs The Point to add to
 * @param rhs The Point to add from
 *
 * @returns The subtracted point
 */
template <class Coordinate>
dashee::Point<Coordinate> dashee::operator+(
	const dashee::Point<Coordinate> & lhs,
	const dashee::Point<Coordinate> & rhs
    )
{
    return dashee::Point<Coordinate>(
            lhs.getX() + rhs.getX(),
            lhs.getY() + rhs.getY(),
            lhs.getZ() + rhs.getZ()
        );
}

/**
 * Subtract the values of the rhs parameter to this object
 *
 * @param lhs The Point to subtract to
 * @param rhs The Point to subtract from
 *
 * @returns The subtracted point
 */
template <class Coordinate>
dashee::Point<Coordinate> dashee::operator-(
	const dashee::Point<Coordinate> & lhs,
	const dashee::Point<Coordinate> & rhs
    )
{
    return dashee::Point<Coordinate>(
            lhs.getX() - rhs.getX(),
            lhs.getY() - rhs.getY(),
            lhs.getZ() - rhs.getZ()
        );
}

/**
 * Multiply the value of of two Points 
 *
 * @param lhs The value to multiply all coordinates by
 * @param rhs The value to multiply all coordinates by
 *
 * @returns The multiplied point
 */
template <class Coordinate>
dashee::Point<Coordinate> dashee::operator*(
        const Point<Coordinate> & lhs,
	const Coordinate & rhs
    )
{
    return dashee::Point<Coordinate>(
            lhs.getX() * rhs,
            lhs.getY() * rhs,
            lhs.getZ() * rhs
        );
}

/**
 * Multiply the value of a point with a template type
 *
 * @param lhs The template parameter to multiply from
 * @param rhs The point to multiply to
 */
template <class Coordinate>
dashee::Point<Coordinate> dashee::operator*(
        const Coordinate & lhs,
        const Point<Coordinate> & rhs
    )
{
    return operator*(rhs, lhs);
}

#endif
