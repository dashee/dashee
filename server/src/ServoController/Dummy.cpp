#include <dashee/ServoController/Dummy.h>

using namespace dashee;

/**
 * Construct.
 *
 * This constructor opens a stream to the file name, so it can be used for 
 * read and write operations. Our file is in binary so we fopen in binary mode
 *
 * We also pass the device name in a constructor
 *
 * @param dev The name of the device which will be open
 * @param channels The number of channels to set
 *
 * @throws ExceptionServoController If device opening fails, an exception will be thrown
 */
ServoControllerDummy::ServoControllerDummy(const char * dev, const unsigned short int channels) : ServoController(dev)
{
    fd = fopen(this->dev, "r+b");

    if (fd == NULL)
        throw ExceptionServoController();

    // Create a servo class for each, servo channel that exists
    for (int x = 0; x < channels; x++)
        servos.push_back(new ServoDummy(fd, x));
    
    //Make sure the binary file is of correct size
    fseek(fd, 0, SEEK_END);
    if (ftell(fd) != (ServoDummy::headerByteSize + (ServoDummy::channelByteSize * channels)))
        throw ExceptionServoController("The binary file is of invalid size. Please create one with 'dd if=/dev/zero of=data/Servo.bin bs=1 count=0 seek=38'");
}

/**
 * Get the last Error.
 *
 * The function gets the error from the file, The error is stored in the first two bytes
 *
 * The response is returned in a two byte represented by char, Only one bit is always set in
 * these two bytes, The error number is represeted by the nth bit set, For example
 * 
 *  00010000|00000000 - Will suggest Errornumber 3, as the erronumbering starts from 0
 * 
 * @returns The error int response
 */
short int ServoControllerDummy::getError()
{
    fseek(fd, 0, SEEK_SET);
    return (short int)sqrt(fgetc(fd) + (256*fgetc(fd)));
}

/**
 * Destruct.
 *
 * Handler to close our ServoControllerDummy::fd opened device
 */
ServoControllerDummy::~ServoControllerDummy()
{
    fclose(this->fd);    
}
