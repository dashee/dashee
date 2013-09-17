/**
 * @file include/dashee/Servo/UART.h
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

#ifndef SERVO_UART_H_
#define SERVO_UART_H_

#include <dashee/Servo.h>

namespace dashee
{
    class ServoUART;
}

/**
 * Servo UART.
 *
 * This is a class which handels communications with the Pololu board
 * it is a wrapper over the read and write commands sent to usually `/dev/ttyAMA0`
 *
 * This class represents one servo/channel at a time, The handle is held externally
 * usually in the ServoController class, or its ServoController<CounterPart> version
 */
class dashee::ServoUART : public dashee::Servo
{
private:

protected:
    
    /** 
     * File Handle.
     *
     * The pointer of the filedescriptor held by ServoController,
     * we use this to actually read and write to the device
     */
    int * fd;
    
public:
    //Open our Servo Device
    explicit ServoUART(int *, const unsigned short int);

    //Get the target of a given channel
    unsigned short int getTarget();

    //Set the target of a given channel
    void setTarget(unsigned short int);
    
    //Close the device
    ~ServoUART();
};

#endif
