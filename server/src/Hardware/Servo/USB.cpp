#include <dashee/Hardware/Servo/USB.h>

using namespace dashee::Hardware;

/**
 * Constructor.
 *
 * The constructor of servo which takes in the device to open usually the device
 * is `/dev/ttyACM0` but this could be different going from system to system
 *
 * @param fd The file handle to the devices that is open
 * @param channel The channel which this servo represents.
 *
 * @throws Exception_Servo If device opening fails, an exception will be thrown
 */
ServoUSB::ServoUSB(int * fd, const unsigned short int channel) : Servo(channel)
{
    this->fd = fd;
}

/**
 * Set the target.
 *
 * This sets the target of a channel given a servo. The target value is between
 * 0-100, the value is converted to the actual target using the 
 * calculateTarget() function.
 *
 * Once we have a target value, we build the command. The command for the board 
 * is represented in 4 bytes, where the first byte represent the set command, 
 * the second represents the channel, and the 3rd and 4rth represent the value. 
 * Note that the 4th and third byte have there Most significant byte set to 0.
 *
 * @param target Our target to set represented in 2 byte, with a value of 0-255
 *
 * @throws ExceptionServo If writing to the board fails
 */
void ServoUSB::setTarget(unsigned short int target)
{
    try
    {
        map<unsigned short int>(target, 0, 255, SERVO_LOW, SERVO_HIGH);
     
        unsigned char command[4];
        command[0] = 0x84;
        command[1] = this->channel;

        // Given an integer needs to be crammed into 2 bytes, with there MSB
        // Set to 0, we need to use 
        //    target & 01111111; to zero our MSB
        // 
        // Then shift the remaining bits and AND by 127
        //       (101010101 >> 7) & 011111111
        // Given us a 2 byte target number with there MSB cleared.
        command[2] = target & 127;
        command[3] = (target >> 7) & 127;

        if (write(*this->fd, command, sizeof(command)) == -1)
            throw ExceptionServo();
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
 * Get the target.
 *
 * This command gets the target of a given channel.
 * To do this however we first need to write to the servo telling it that we 
 * want the target value, of our given `channel`. We then read from the board, 
 * which returns the value in a 2 bytes which in collation represent one number.
 * 
 * The value's returned can range from 992 - 8000
 * 
 * The command to tell the servo that we want channel number requires two bytes 
 * the first tells is we are using getTarget from the board, and the second 
 * tells it which channel The byte to get is 0x90 as set by Pololu
 *
 * @param fromcache If set to true, returns the Class value rather than querying
 *  the servo
 *
 * @throws ExceptionServo If a read write error occurs
 *
 * @returns The Target value of a channel 
 */
unsigned short int ServoUSB::getTarget(const bool fromcache)
{
    if (fromcache)
        return this->target;

    unsigned char command[2];
    command[0] = 0x90;
    command[1] = static_cast<char>(this->channel);

    if(write(*fd, command, sizeof(command)) == -1)
        throw ExceptionServo();

    unsigned char response[2];
    if(read(*fd,response,2) != 2)
        throw ExceptionServo("Invalid Target");

    return dashee::map<unsigned short int>(
        response[0] + 256*response[1],
        SERVO_LOW,
        SERVO_HIGH,
        0,
        255
    );
}

/**
 * Destructor.
 *
 * Does nothing
 */
ServoUSB::~ServoUSB()
{
}
