/**
 * This is a class which handels communications with the Pololu board
 * it is a wrapper over the read and write commands sent to usually /dev/ttyACM0
 * 
 * The /dev/ttyACM0 is OS dependant, and be use a later Numerical value if the OS
 * alread has a device running with the similar name
 * 
 * You can see the full documentaion of the Pololu boart at http://www.pololu.com/docs/0J40/all
 * Please read and understand the above to understand in detail the protocol's used in this code
 *
 * @author Shahmir Javaid
 */

#ifndef SERVOCONTROLLER_USB_H_
#define SERVOCONTROLLER_USB_H_

#include "../ServoController.h"
#include "../Servo/USB.h"

class ServoController_USB : public ServoController
{
private:

protected:
        
    /**
     * Given our @dev variable we open this device, which returns the appropriate
     * file handler.
     */
    int fd;
    
public:
    // Open our device, and set our @servos array
    explicit ServoController_USB(const char *, const unsigned short int = 8);
    
    // Get the error from the board
    virtual short int getError();
    
    // Close the device
    virtual ~ServoController_USB();
};

#endif
