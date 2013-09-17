/**
 * @file include/dashee/ServoController/UART.h
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

#ifndef SERVOCONTROLLER_UART_H_
#define SERVOCONTROLLER_UART_H_

#include <termios.h>

#include <dashee/GPIO.h>
#include <dashee/ServoController.h>
#include <dashee/Servo/UART.h>

namespace dashee
{
    class ServoControllerUART;
}

/**
 * This is a class which handels communications with the Pololu board
 * it is a wrapper over the read and write commands sent to usually `/dev/ttyAMA0`
 * 
 * The `/dev/ttyAMA0` is OS dependant, and be use a later Numerical value if the OS
 * alread has a device running with the similar name
 *
 * The `/dev/ttyAMA0` represents the UART protocol, and the pololu board is set to
 * `UART detect baud rate`. However this means the device baud rate is set by the 
 * constructor
 */
class dashee::ServoControllerUART : public dashee::ServoController
{
private:

protected:
        
    /**
     * File Handle.
     *
     * Given our ServoController::dev variable we open this device, 
     * which returns the appropriate file handler.
     */
    int fd;
    
    // Reset our board by driving the reset pin low
    void reset();
    
    // Initialize our board
    void init();
    
public:
    // Open our device, and set our ServoController::servos array
    explicit ServoControllerUART(const char * dev, const unsigned short int channels = 6);
    
    // Get the error from the board
    virtual short int getError();
    
    // Close the device
    virtual ~ServoControllerUART();
};

#endif
