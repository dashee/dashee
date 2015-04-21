/**
 * @file include/dashee/Hardware/Servo/UART.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_HARDWARE_SERVO_UART_H_
#define DASHEE_HARDWARE_SERVO_UART_H_

#include <dashee/Hardware/Servo.h>

namespace dashee
{
    namespace Hardware
    {
        class ServoUART;
    }
}

/**
 * Servo UART.
 *
 * This is a class which handles communications with the Pololu board it is a 
 * wrapper over the read and write commands sent to usually `/dev/ttyAMA0`
 *
 * This class represents one servo/channel at a time, The handle is held 
 * externally usually in the ServoController class, or its 
 * ServoController<CounterPart> version
 */
class dashee::Hardware::ServoUART : public dashee::Hardware::Servo
{
private:

protected:
    
    /** 
     * File Handle.
     *
     * The pointer of the file descriptor held by ServoController,
     * we use this to actually read and write to the device
     */
    int * fd;

    //Set the target of a given channel
    void setPhysicalTarget(unsigned short int target);
    unsigned short int getPhysicalTarget();
    
public:
    //Open our Servo Device
    explicit ServoUART(int * fd, const unsigned short int channel);
    
    //Close the device
    ~ServoUART();
};

#endif
