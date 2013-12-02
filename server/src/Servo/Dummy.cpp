#include <dashee/Servo/Dummy.h>

using namespace dashee;

/**
 * Construct.
 *
 * This constructor opens a stream to the file name, so it can be used for 
 * read and write operations. Our file is in binary so we fopen in binary mode.
 * We also pass the device name in a constructor
 *
 * @param fd The file handle used by the Servo to read/write to the servo
 * @param channel The channel number this servo class represents
 */
ServoDummy::ServoDummy(FILE * fd, const unsigned short int channel) 
    : Servo(channel)
{
    this->fd = fd;
    memset(this->buffer, 0, sizeof(unsigned char)*2);
}

/**
 * Set the target value.
 *
 * This function will write to our binary file give a channel number.
 * The target is always written to the first two bytes of the channel.
 *
 * @param target Target to set represented in 2 byte, with a value of 0-255
 *
 * @throws ExceptionServo If writing to the board fails
 *                        or a ExceptionInvalidValue is caught
 */
void ServoDummy::setTarget(unsigned short int target)
{
    try
    {
        unsigned short int converted 
            = map<unsigned short int>(target, 0, 255, SERVO_LOW, SERVO_HIGH);
            
        if (
            fseek(
                fd, 
                headerByteSize + (((int)this->channel) * channelByteSize), 
                SEEK_SET
            ) != 0
        )
            throw ExceptionServo("Seek failed in setTarget");
        
        //Create our buffer
        buffer[0] = converted;
        buffer[1] = converted >> 8;
        
        //Write to our servo
        fwrite((const char *)buffer, 2, sizeof(buffer), fd);
    }
    catch (ExceptionInvalidValue e)
    {
        throw ExceptionServo(
            "Invalid setTarget(" + dashee::itostr(target) + ")"
        );
    }

    Servo::setTarget(target);
}

/**
 * Get the target value.
 *
 * Seek to the current channel, and retrieve the first 2 bytes
 * which hold the target information. Make sure to flush any write data
 * left over otherwise things will start looking messy.
 *
 * @param fromcache If set to true, then call the parent function
 *
 * @throws ExceptionServo If a read write error occurs
 *
 * @returns The target value of the servo.
 */
unsigned short int ServoDummy::getTarget(const bool fromcache)
{
    if (fromcache)
        return this->target;

    if (
        fseek(
            fd, 
            headerByteSize + (((int)this->channel) * channelByteSize), 
            SEEK_SET
        ) != 0
    )
        throw ExceptionServo("Seek failed in getTarget");

    //Flush the stream, as we write one byte at a time
    fflush(fd);
    if (fread(buffer, 2, sizeof(buffer), fd) != 2)
        throw ExceptionServo("Reading 2 bytes failed in getTarget");
    
    return map<unsigned short int>(
        buffer[0] + 256*buffer[1], 
        SERVO_LOW, 
        SERVO_HIGH,
        0, 
        255
    );
}

/**
 * Destruct.
 */
ServoDummy::~ServoDummy()
{
}
