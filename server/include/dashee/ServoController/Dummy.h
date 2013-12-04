/**
 * @file include/dashee/ServoController/Dummy.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_SERVOCONTROLLER_DUMMY_H_
#define DASHEE_SERVOCONTROLLER_DUMMY_H_

#include <dashee/ServoController.h>
#include <dashee/Servo/Dummy.h>

namespace dashee
{
    class ServoControllerDummy;
}

/**
 * The Dummy ServoController, used for testing.
 *
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
 */
class dashee::ServoControllerDummy : public dashee::ServoController
{
private:

    /**
     * File handle.
     *
     * Given our ServoController::dev variable we open this device, 
     * which returns the appropriate file handler for the stream
     */
    FILE * fd;

protected:
    
public:
    // Open our Servo Device
    explicit ServoControllerDummy(
            const char * dev, 
            const unsigned short int channel
        );
    
    // Get the error from file
    virtual short int getError() const;

    // Close the device
    virtual ~ServoControllerDummy();
};

#endif
