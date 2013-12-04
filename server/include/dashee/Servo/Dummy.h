/**
 * @file include/dashee/Servo/Dummy.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_SERVO_DUMMY_H_
#define DASHEE_SERVO_DUMMY_H_

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
 * This class represents one servo/channel at a time, The handel is held 
 * externally usually in the ServoController class, or its 
 * ServoController<CounterPart> version
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
     * The controller needs to be able to access channelByteSize and 
     * headerByteSize for initialization checks, so we nee to create a 
     * friendship.
     */
    friend class ServoControllerDummy;
    
public:
    //Open our Servo Device
    explicit ServoDummy(FILE * fd, const unsigned short int channel);

    //Set the target of a given channel
    void setTarget(unsigned short int target);
    unsigned short int getTarget(const bool fromcache = false);
    
    //Close the device
    ~ServoDummy();
};

#endif
