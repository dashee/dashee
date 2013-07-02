/**
 * This is a class which handels communications with the Pololu board
 * it is a wrapper over the read and write commands sent to usually /dev/ttyACM0
 *
 * This class represents one servo/channel at a time, The handel is held externally
 * usually in the ServoController class, or its ServoController_<CounterPart> version
 *
 * @author Shahmir Javaid
 */

#ifndef SERVO_USB_H_
#define SERVO_USB_H_

#include "../Servo.h"

class Servo_USB : public Servo
{
private:
    

protected:
    
    /** 
     * The pointer of the filedescriptor help by ServoController,
     * we use this to actually read and write to the device
     */
    int * fd;
    
public:
    //Open our Servo Device
    explicit Servo_USB(int *, const unsigned short int);

    //Get the target of a given channel
    unsigned short int getTarget();

    //Set the target of a given channel
    void setTarget(unsigned short int);
    
    //Close the device
    ~Servo_USB();
};

#endif
