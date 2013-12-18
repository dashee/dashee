/**
 * @file include/dashee/Coordinate.tpp
 * @author Shahmir Javaid
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_COORDINATE_TPP_
#define DASHEE_COORDINATE_TPP_

/**
 * Construct the values and set all to 0's
 */
template <class T> dashee::Coordinate<T>::Coordinate()
{
    memset(&this->x, 0, sizeof(T));
    memset(&this->y, 0, sizeof(T));
    memset(&this->z, 0, sizeof(T));
}

/**
 * Set the value of the coordinates from the outset of the construction
 *
 * @param x The value of X
 * @param y The value of Y
 * @param z The value of Z
 */
template <class T> dashee::Coordinate<T>::Coordinate(
	const T x, 
	const T y, 
	const T z
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
template <class T> void dashee::Coordinate<T>::setX(const T x)
{
    this->x = x;
}

/**
 * Set the value of Y
 *
 * @param y the value to set
 */
template <class T> void dashee::Coordinate<T>::setY(const T y)
{
    this->y = y;
}

/**
 * Set the value of Z
 *
 * @param z the value to set
 */
template <class T> void dashee::Coordinate<T>::setZ(const T z)
{
    this->z = z;
}

/**
 * Return the value of X
 *
 * @returns value of x
 */
template <class T> T dashee::Coordinate<T>::getX() const
{
    return x;
}

/**
 * Return the value of Y
 *
 * @returns value of y
 */
template <class T> T dashee::Coordinate<T>::getY() const
{
    return y;
}

/**
 * Return the value of Z
 *
 * @returns value of z
 */
template <class T> T dashee::Coordinate<T>::getZ() const
{
    return z;
}

/**
 * Operator which tests the equality of two coordinates.
 *
 * @param rhs The right hand side to test against
 */
template <class T> 
bool dashee::Coordinate<T>::operator ==(const dashee::Coordinate<T>& rhs) const
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
template <class T> 
bool dashee::Coordinate<T>::operator !=(const dashee::Coordinate<T>& rhs) const
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
template <class T>
dashee::Coordinate<T> dashee::Coordinate<T>::operator+(
	const dashee::Coordinate<T> &rhs
    )
{
    dashee::Coordinate<T> result;
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
template <class T>
dashee::Coordinate<T> dashee::Coordinate<T>::operator-(
	const dashee::Coordinate<T> &rhs
    )
{
    dashee::Coordinate<T> result;
    result.setX(this->getX() - rhs.getX());
    result.setY(this->getY() - rhs.getY());
    result.setZ(this->getZ() - rhs.getZ());

    return result;
}

/**
 * Do nothing destruct
 */
template <class T> dashee::Coordinate<T>::~Coordinate()
{

}

#endif

