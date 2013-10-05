/**
 * @file include/dashee/ServoController/USB.h
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
 *                     you may distribute the resulting work only under a licence 
 *                     identical to this one.
 *
 * The terms and conditions are updated at http://dashee.co.uk/license. View the
 * project site for more details
 */

#ifndef DASHEE_SERVOCONTROLLER_USB_H_
#define DASHEE_SERVOCONTROLLER_USB_H_

#include <dashee/ServoController.h>
#include <dashee/Servo/USB.h>

namespace dashee
{
    class ServoControllerUSB;
}

/**
 * This is a class which handels communications with the Pololu board
 * it is a wrapper over the read and write commands sent to usually `/dev/ttyACM0`
 * 
 * The `/dev/ttyACM0` is OS dependant, and be use a later Numerical value if the OS
 * alread has a device running with the similar name
 * 
 * You can see the full documentaion of the Pololu boart at http://www.pololu.com/docs/0J40/all
 * Please read and understand the above to understand in detail the protocol's used in this code
 */
class dashee::ServoControllerUSB : public dashee::ServoController
{
private:

protected:
        
    /**
     * File handle.
     *
     * Given our ServoController::dev variable we open this device, 
     * which returns the appropriate file handler.
     */
    int fd;
    
public:
    // Open our device, and set our ServoController::servos array.
    explicit ServoControllerUSB(const char *, const unsigned short int = 8);
    
    // Get the error from the board
    virtual short int getError();
    
    // Close the device
    virtual ~ServoControllerUSB();
};

#endif
