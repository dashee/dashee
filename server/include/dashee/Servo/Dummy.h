/**
 * @file include/dashee/Servo/Dummy.h
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

#ifndef SERVO_DUMMY_H_
#define SERVO_DUMMY_H_

#include <dashee/Servo.h>

namespace dashee
{
    class ServoDummy;
}

/**
 * Servo Dummy class for testing.
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
 * This program presumes that there are SERVO_DUMMY_CHANNEL's in our file.
 *
 * This class represents one servo/channel at a time, The handel is held externally
 * usually in the ServoController class, or its ServoController<CounterPart> version
 */
class dashee::ServoDummy : public dashee::Servo
{
private:

    /**
     * Header byte size.
     *
     * Holds the value of the header byte size
     */
    static const unsigned short int headerByteSize = 2;

    /**
     * Per Channel byte size.
     *
     * Holds the value of the channels byte size
     */
    static const unsigned short int channelByteSize = 6;
    
    /**
     * The temp buffer used for read/write.
     *
     * 2 Byte buffere used to read and write to our binary file
     */
    unsigned char buffer[2];

protected:
    
    /**
     * File Handle.
     *
     * The pointer of the filedescriptor held by ServoController,
     * we use this to actually read and write to the device
     */
    FILE * fd;
    
    
    /**
     * The controller needs to be able to access channelByteSize and headerByteSize
     * for initialization checks, so we nee to create a friendship. 
     */
    friend class ServoControllerDummy;
    
public:
    //Open our Servo Device
    explicit ServoDummy(FILE *, const unsigned short int);

    //Get the target of a given channel
    unsigned short int getTarget();

    //Set the target of a given channel
    void setTarget(unsigned short int);
    
    //Close the device
    ~ServoDummy();
};

#endif
