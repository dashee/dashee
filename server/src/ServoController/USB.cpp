#include <dashee/ServoController/USB.h>

using namespace dashee;

/**
 * Construct.
 *
 * The constructor of servo which takes in the device to open
 * usually the device is `/dev/ttyACM0` but this could be different going from system to system
 *
 * @param dev The name of the device which will be open
 * @param channels The number of channels to set
 *
 * @throw ExceptionServoController If device opening fails, an exception will be thrown
 */
ServoControllerUSB::ServoControllerUSB(const char * dev, const unsigned short int channels) : ServoController(dev)
{
    this->fd = open(this->dev, O_RDWR | O_NOCTTY);

    if (fd == -1)
        throw ExceptionServoController();
    
    // Create a servo class for each, servo channel that exists
    for (int x = 0; x < channels; x++)
        this->servos.push_back(new ServoUSB(&this->fd, x));
}

/**
 * Destruct.
 *
 * Handler to close our ServoControllerUSB::fd opened device, and delete all servo's.
 */
ServoControllerUSB::~ServoControllerUSB()
{
    close(this->fd);
}

/**
 * Get last known error.
 *
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
 * @throws ExceptionServoController If read/write fails
 *
 * @returns The error code
 */
short int ServoControllerUSB::getError()
{
    unsigned char command[] = { 0xA1 };
    unsigned char response[2];

    if (write(this->fd, command, sizeof(command)) == -1)
        throw ExceptionServoController();
    
    if(read(this->fd, response,2) != 2)
        throw ExceptionServoController();
    
    //TODO This needs to be fixed, its wrong at the moment
    return (short int)sqrt(response[0] + 256*response[1]);
}
