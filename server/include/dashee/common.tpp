/**
 * @file include/dashee/common.h
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

#ifndef DASHEE_COMMON_TPP_
#define DASHEE_COMMON_TPP_

/**
 * Map from a given from-range to a given to-range
 *
 * A usefull function which allows to convert a value from a given range known
 * as from and convert it into a range called high. The values can be inversed,
 * at the to or from point.
 *
 * @param value The value to convert
 * @param fromLow the low range value to convert from
 * @param fromHigh the high range value to convert to
 * @param toLow The low range value to convert to
 * @param toHigh The high range value to convert to
 *
 * @throws ExceptionInvalidValue When ranges are not correct.
 * @throws Exception on divide by 0
 */
template<class T> void dashee::map(
    T *value, 
    T fromLow, 
    T fromHigh, 
    T toLow, 
    T toHigh
)
{
    if (*value < fromLow)
	throw ExceptionInvalidValue(
	    "The value in dashee::map was not within its low from range."
	);
    else if (*value > fromHigh)
	throw ExceptionInvalidValue(
	    "The value in dashee::map was not within its high from range."
	);

    double fromRange = (double)(fromHigh - fromLow);
    double toRange = (double)(toHigh - toLow);

    if (fromRange == 0)
	throw Exception("Division by 0 in dashee::map for fromRange");

    double scaled = ((double)*value - fromLow) / fromRange;

    *value = static_cast<T>(round((double)toLow + (scaled * toRange)));
}

/**
 * Same as the map with the value as a pointer. except
 * this returns the modified value.
 *
 * @param value The value to convert
 * @param fromLow the low range value to convert from
 * @param fromHigh the high range value to convert to
 * @param toLow The low range value to convert to
 * @param toHigh The high range value to convert to
 *
 * @returns The converted value
 */ 
template <class T> T dashee::map(
    T value, 
    T fromLow, 
    T fromHigh, 
    T toLow, 
    T toHigh
)
{
    dashee::map(&value, fromLow, fromHigh, toLow, toHigh);
    return value;
}

/**
 * A function which returns the min or max value if it is out of range.
 *
 * Note if min is greater than max, then the values are inversed, and the 
 * reverse is represented, so for example if min is 255 and max is 0 the value
 * sent was 257 the returned value will be 255. or -1 would represent 0. In
 * normal mode 0-255 257 will still return 255,
 *
 * @param value The value to check
 * @param min return min if the value is less than min
 * @param max return max if the value is greater than max
 */
template<class T> void dashee::constrain(T *value, T min, T max)
{
    if (*value < min)
        *value = min;
    else if (*value > max)
        *value = max;
}

#endif
