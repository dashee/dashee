/**
 * @file include/dashee/Buffer.tpp
 * @author Shahmir Javaid
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_BUFFER_TPP_
#define DASHEE_BUFFER_TPP_

/**
 * Get the next element, and delete it from the queue
 *
 * @return the next element
 */
template <class T> T dashee::Buffer<T>::next()
{
    if (this->empty())
	throw dashee::Exception("Trying to call next on an empty Buffer");

    T temp = this->front();
    this->pop();
    return temp;
}

#endif
