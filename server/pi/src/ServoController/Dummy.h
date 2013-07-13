/**
 * This class defines the implementation to a binary file
 * which pretends to be a servo, It is usefull for testing
 * if you don't have a board.
 *
 * The binary file represents the first two bytes as the error number
 * and consecative 4 bytes represent a channel, of these four bytes
 * the first represents the channel number, the second Target, the third Speed
 * and the last acceleration. 
 *
 * This program presumes that there are SERVO_DUMMY_CHANNEL's in our file
 *
 * @author Shahmir Javaid
 */

#ifndef SERVOCONTROLLER_DUMMY_H_
#define SERVOCONTROLLER_DUMMY_H_

#include "../ServoController.h"
#include "../Servo/Dummy.h"

class ServoControllerDummy : public ServoController
{
private:

    /**
     * Given our @dev variable we open this device, which returns the appropriate
     * file handler for the stream
     */
    FILE * fd;

protected:
    
public:
    // Open our Servo Device
    explicit ServoControllerDummy(const char *, const unsigned short int channel);
    
    // Get the error from file
    virtual short int getError();

    // Close the device
    virtual ~ServoControllerDummy();
};

#endif
