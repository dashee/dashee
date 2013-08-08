#include "USB.h"

/**
 * The constructor of servo which takes in the device to open
 * usually the device is /dev/ttyACM0 but this could be different going from system to system
 *
 * @param (const char *)dev - The name of the device which will be open
 * @throw Exception_Servo - If device opening fails, an exception will be thrown
 */
ServoControllerUSB::ServoControllerUSB(const char * dev, const unsigned short int channels) : ServoController(dev)
{
    this->fd = open(this->dev, O_RDWR | O_NOCTTY);

    if (fd == -1)
        throw Exception_ServoController();
    
    // Create a servo class for each, servo channel that exists
    for (int x = 0; x < channels; x++)
        servos.push_back(new ServoUSB(&this->fd, x));
}

/**
 * Handler to close our @fd opened device, and delete all servo's
 */
ServoControllerUSB::~ServoControllerUSB()
{
    close(this->fd);
}

/**
 * The Pololu board provides a error handling, This function is designed to 
 * get the last error from the Pololy Maestro USB Servo board, Note on retriving 
 * the error, the error is reset. So it is always a good idea to periodicly
 * pole the board.
 *
 * For performance reason we allow the user to worry about errors at his/hers perfernce
 *
 * The response is returned in a two byte represented by char, Only one bit is always set in
 * these two bytes, The error number is represeted by the nth bit set, For example
 * 
 *  00010000|00000000 - Will suggest Errornumber 3, as the erronumbering starts from 0
 * 
 * @reuturn short int - The integer response
 */
short int ServoControllerUSB::getError()
{
    unsigned char command[] = { 0xA1 };
    unsigned char response[2];

    if (write(this->fd, command, sizeof(command)) == -1)
        throw Exception_ServoController();
    
    if(read(this->fd, response,2) != 2)
        throw Exception_ServoController();
    
    //TODO This needs to be fixed, its wrong at the moment
    return (short int)sqrt(response[0] + 256*response[1]);
}
