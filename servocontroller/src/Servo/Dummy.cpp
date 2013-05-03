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
Servo_Dummy::Servo_Dummy(const char * dev) : Servo(dev)
{
    fd = fopen(this->dev, "r+b");

    if (fd == NULL)
        throw Exception_Servo();
    
    //Make sure the binary file is of correct size
    fseek(fd, 0, SEEK_END);
    if (ftell(fd) != (headerByteSize + (channelByteSize * 6)))
        throw Exception_Servo("The binary file is of invalid size. Please create one with 'dd if=/dev/zero of=data/Servo.bin bs=1 count=0 seek=38'");

}

/**
 * Handler to close our @fd opened device
 */
Servo_Dummy::~Servo_Dummy()
{
    fclose(this->fd);    
}

/**
 * The function gets the error from the file, The error is stored in the first two bytes
 *
 * The response is returned in a two byte represented by char, Only one bit is always set in
 * these two bytes, The error number is represeted by the nth bit set, For example
 * 
 *  00010000|00000000 - Will suggest Errornumber 3, as the erronumbering starts from 0
 * 
 * @reuturn short int - The integer response
 */
short int Servo_Dummy::getError()
{
    fseek(fd, 0, SEEK_SET);
    return (short int)sqrt(fgetc(fd) + (256*fgetc(fd)));
}

/**
 * Seek to the current channel, and retrieve the first 2 bytes
 * which hold the target information. Make sure to flush any write data
 * left over otherwise things will start looking messy.
 *
 * @param (const unsigned char)channel - The Channel to get
 * 
 * @throw Exception_Servo() - If a read write error occurs
 *
 * @return int - The value of the channel 
 */
unsigned short int Servo_Dummy::getTarget(const unsigned char channel)
{
    if (fseek(fd, headerByteSize + (((int)channel-1) * channelByteSize), SEEK_SET) != 0)
        throw Exception_Servo("Seek failed in getTarget");

    //Flush the stream, as we write one byte at a time
    fflush(fd);
    if (fread(buffer, 2, sizeof(buffer), fd) != 2)
        throw Exception_Servo("Reading 2 bytes failed in getTarget");
    
    return buffer[0] + 256 * buffer[1];
}

/**
 * This function will write to our binary file give a channel number.
 * The target is always written to the first two bytes of the channel.
 *
 * @param (const unsigned char)channel - The channel number represented in one byte
 * @paran (short int)target - Our target to set represented in 2 byte, with a value of 0-100
 *
 * @throw Exception_Servo - If writing to the board fails
 */
void Servo_Dummy::setTarget(const unsigned char channel, unsigned short int target)
{
    calculateTarget(target);
        
    if (fseek(fd, headerByteSize + (((int)channel-1) * channelByteSize), SEEK_SET) != 0)
        throw Exception_Servo("Seek failed in setTarget");
    
    //Create our buffer
    buffer[0] = target;
    buffer[1] = target >> 8;
    
    //Write to our servo
    fwrite((const char *)buffer, 2, sizeof(buffer), fd);
}

/**
 * TODO finish the implimentation of this function
 */
int Servo_Dummy::getChannels()
{
    return 0;      
}
