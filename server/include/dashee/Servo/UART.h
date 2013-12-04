/**
 * @file include/dashee/Servo/UART.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_SERVO_UART_H_
#define DASHEE_SERVO_UART_H_

#include <dashee/Servo.h>

namespace dashee
{
    class ServoUART;
}

/**
 * Servo UART.
 *
 * This is a class which handels communications with the Pololu board it is a 
 * wrapper over the read and write commands sent to usually `/dev/ttyAMA0`
 *
 * This class represents one servo/channel at a time, The handle is held 
 * externally usually in the ServoController class, or its 
 * ServoController<CounterPart> version
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
    explicit ServoUART(int * fd, const unsigned short int channel);

    //Set the target of a given channel
    void setTarget(unsigned short int target);
    unsigned short int getTarget(const bool fromcache = false);
    
    //Close the device
    ~ServoUART();
};

#endif
