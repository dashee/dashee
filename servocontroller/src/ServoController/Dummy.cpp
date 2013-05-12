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
ServoController_Dummy::ServoController_Dummy(const char * dev, const unsigned short int channels) : ServoController(dev)
{
    fd = fopen(this->dev, "r+b");

    if (fd == NULL)
        throw Exception_ServoController();

    // Create a servo class for each, servo channel that exists
    for (int x = 0; x < channels; x++)
        servos.push_back(new Servo_Dummy(fd, x));
}

/**
 * Handler to close our @fd opened device
 */
ServoController_Dummy::~ServoController_Dummy()
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
short int ServoController_Dummy::getError()
{
    fseek(fd, 0, SEEK_SET);
    return (short int)sqrt(fgetc(fd) + (256*fgetc(fd)));
}
