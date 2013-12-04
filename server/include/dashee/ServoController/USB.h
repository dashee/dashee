/**
 * @file include/dashee/ServoController/USB.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
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
 * This is a class which handels communications with the Pololu board it is a 
 * wrapper over the read and write commands sent to usually `/dev/ttyACM0`
 * 
 * The `/dev/ttyACM0` is OS dependant, and be use a later Numerical value if the
 * OS already has a device running with the similar name
 * 
 * You can see the full documentaion of the Pololu boart at 
 * http://www.pololu.com/docs/0J40/all Please read and understand the above to 
 * understand in detail the protocol's used in this code
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
    explicit ServoControllerUSB(
            const char * dev, 
            const unsigned short int channel = 8
        );
    
    // Get the error from the board
    virtual short int getError() const;
    
    // Close the device
    virtual ~ServoControllerUSB();
};

#endif
