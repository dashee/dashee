#include "Dummy.h"

/**
 * This constructor opens a stream to the file name, so it can be used for 
 * read and write operations. Our file is in binary so we fopen in binary mode
 *
 * We also pass the device name in a constructor
 *
 * @param (const char *)dev - The name of the device which will be open
 * @throw Exception_Servo - If device opening fails, an exception will be thrown
 */
ServoDummy::ServoDummy(FILE * fd, const unsigned short int channel) : Servo(channel)
{
    this->fd = fd;
}

/**
 * Handler to close our @fd opened device
 */
ServoDummy::~ServoDummy()
{
}

/**
 * Seek to the current channel, and retrieve the first 2 bytes
 * which hold the target information. Make sure to flush any write data
 * left over otherwise things will start looking messy.
 *
 * @throw Exception_Servo() - If a read write error occurs
 *
 * @return int - The value of the channel 
 */
unsigned short int ServoDummy::getTarget()
{
    if (fseek(fd, headerByteSize + (((int)this->channel) * channelByteSize), SEEK_SET) != 0)
        throw Exception_Servo("Seek failed in getTarget");

    //Flush the stream, as we write one byte at a time
    fflush(fd);
    if (fread(buffer, 2, sizeof(buffer), fd) != 2)
        throw Exception_Servo("Reading 2 bytes failed in getTarget");
    
    return TargetToPercentage((buffer[0] + 256 * buffer[1]));
}

/**
 * This function will write to our binary file give a channel number.
 * The target is always written to the first two bytes of the channel.
 *
 * @param (short int)target - Our target to set represented in 2 byte, with a value of 0-100
 *
 * @throw Exception_Servo - If writing to the board fails
 */
void ServoDummy::setTarget(unsigned short int target)
{
    PercentageToTarget(&target);
        
    if (fseek(fd, headerByteSize + (((int)this->channel) * channelByteSize), SEEK_SET) != 0)
        throw Exception_Servo("Seek failed in setTarget");
    
    //Create our buffer
    buffer[0] = target;
    buffer[1] = target >> 8;
    
    //Write to our servo
    fwrite((const char *)buffer, 2, sizeof(buffer), fd);
}
