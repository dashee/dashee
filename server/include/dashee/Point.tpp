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
template <class Coordinate> void dashee::Point<Coordinate>::setX(const Coordinate x)
{
    this->x = x;
}

/**
 * Set the value of Y
 *
 * @param y the value to set
 */
template <class Coordinate> void dashee::Point<Coordinate>::setY(const Coordinate y)
{
    this->y = y;
}

/**
 * Set the value of Z
 *
 * @param z the value to set
 */
template <class Coordinate> void dashee::Point<Coordinate>::setZ(const Coordinate z)
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
bool dashee::Point<Coordinate>::operator ==(const dashee::Point<Coordinate>& rhs) const
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
bool dashee::Point<Coordinate>::operator !=(const dashee::Point<Coordinate>& rhs) const
{
    return 
	this->x != rhs.getX() ||
	this->y != rhs.getY() ||
	this->z != rhs.getZ();
}

/**
 * Add the values of the rhs parameter to this object
 *
 * @param rhs The right hand side to add from
 */
template <class Coordinate>
dashee::Point<Coordinate> dashee::Point<Coordinate>::operator+(
	const dashee::Point<Coordinate> &rhs
    )
{
    dashee::Point<Coordinate> result;
    result.setX(this->getX() + rhs.getX());
    result.setY(this->getY() + rhs.getY());
    result.setZ(this->getZ() + rhs.getZ());

    return result;
}

/**
 * Subtract the values of the rhs parameter to this object
 *
 * @param rhs The right hand side to add from
 */
template <class Coordinate>
dashee::Point<Coordinate> dashee::Point<Coordinate>::operator-(
	const dashee::Point<Coordinate> &rhs
    )
{
    dashee::Point<Coordinate> result;
    result.setX(this->getX() - rhs.getX());
    result.setY(this->getY() - rhs.getY());
    result.setZ(this->getZ() - rhs.getZ());

    return result;
}

/**
 * Do nothing destruct
 */
template <class Coordinate> dashee::Point<Coordinate>::~Point()
{

}

#endif
