/**
 * @file include/dashee/Hardware/ServoController/Dummy.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_HARDWARE_SERVOCONTROLLER_DUMMY_H_
#define DASHEE_HARDWARE_SERVOCONTROLLER_DUMMY_H_

#include <dashee/Hardware/ServoController.h>
#include <dashee/Hardware/Servo/Dummy.h>

namespace dashee
{
    namespace Hardware
    {
        class ServoControllerDummy;
    }
}

/**
 * The Dummy ServoController, used for testing.
 *
 * This class defines the implementation to a binary file
 * which pretends to be a servo, It is useful for testing
 * if you don't have a board.
 *
 * The binary file represents the first two bytes as the error number
 * and consecutive 4 bytes represent a channel, of these four bytes
 * the first represents the channel number, the second Target, the third Speed
 * and the last acceleration. 
 *
 * This program presumes that there are SERVO_DUMMY_CHANNEL's in our file
 */
class dashee::Hardware::ServoControllerDummy 
    : public dashee::Hardware::ServoController
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
