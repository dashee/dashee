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
 * This program presumes that there are SERVO_DUMMY_CHANNEL's in our file.
 * 
 *
 * This class represents one servo/channel at a time, The handel is held externally
 * usually in the ServoController class, or its ServoController_<CounterPart> version
 *
 * @author Shahmir Javaid
 */

#ifndef SERVO_DUMMY_H_
#define SERVO_DUMMY_H_

//#ifndef SERVO_DUMMY_CHANNEL
//#define SERVO_DUMMY_CHANNEL 6
//#endif

#include "../Servo.h"

class Servo_Dummy : public Servo
{
private:

    /**
     * Given our @dev variable we open this device, which returns the appropriate
     * file handler for the stream
     */
    FILE * fd;
    
    /**
     * Holds the value of the header byte size
     */
    static const unsigned short int headerByteSize = 2;

    /**
     * Holds the value of the channel byte size
     */
    static const unsigned short int channelByteSize = 6;
    
    /**
     * 2 Byte buffere used to read and write to our binary file
     */
    char buffer[2];

protected:
    
public:
    //Open our Servo Device
    explicit Servo_Dummy(FILE *, const unsigned short int);

    //Get the target of a given channel
    unsigned short int getTarget();

    //Set the target of a given channel
    void setTarget(unsigned short int);
    
    //Close the device
    ~Servo_Dummy();
};

#endif
