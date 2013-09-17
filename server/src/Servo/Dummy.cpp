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
ServoDummy::ServoDummy(FILE * fd, const unsigned short int channel) : Servo(channel)
{
    this->fd = fd;
}

/**
 * Destruct.
 */
ServoDummy::~ServoDummy()
{
}

/**
 * Get the target value.
 *
 * Seek to the current channel, and retrieve the first 2 bytes
 * which hold the target information. Make sure to flush any write data
 * left over otherwise things will start looking messy.
 *
 * @throws ExceptionServo If a read write error occurs
 *
 * @returns The target value of the servo.
 */
unsigned short int ServoDummy::getTarget()
{
    if (fseek(fd, headerByteSize + (((int)this->channel) * channelByteSize), SEEK_SET) != 0)
        throw ExceptionServo("Seek failed in getTarget");

    //Flush the stream, as we write one byte at a time
    fflush(fd);
    if (fread(buffer, 2, sizeof(buffer), fd) != 2)
        throw ExceptionServo("Reading 2 bytes failed in getTarget");
    
    return TargetToPercentage((buffer[0] + 256 * buffer[1]));
}

/**
 * Set the target value.
 *
 * This function will write to our binary file give a channel number.
 * The target is always written to the first two bytes of the channel.
 *
 * @param target Target to set represented in 2 byte, with a value of 0-100
 *
 * @throws ExceptionServo If writing to the board fails
 */
void ServoDummy::setTarget(unsigned short int target)
{
    PercentageToTarget(&target);
        
    if (fseek(fd, headerByteSize + (((int)this->channel) * channelByteSize), SEEK_SET) != 0)
        throw ExceptionServo("Seek failed in setTarget");
    
    //Create our buffer
    buffer[0] = target;
    buffer[1] = target >> 8;
    
    //Write to our servo
    fwrite((const char *)buffer, 2, sizeof(buffer), fd);
}
