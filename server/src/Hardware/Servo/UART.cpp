#include <dashee/Hardware/Servo/UART.h>

using namespace dashee::Hardware;

/**
 * Constructor.
 *
 * This constructor will get the fd of the servo device that is open by 
 * its parrent ServoControllerUART class. The fd is used to talk to the 
 * servo
 *
 * @param fd The file handle to the servo used for read/write
 * @param channel The channel which this ServoUART class represents
 *
 * @throws Exception_Servo If device opening fails, an exception will be thrown
 */
ServoUART::ServoUART(int * fd, const unsigned short int channel) 
    : Servo(channel), fd(fd)
{
}

/**
 * Set the target.
 *
 * This function will talk to our board and set the specific channel to the 
 * required byte
 *
 * The command to tell the servo that we want to set channel number requires 6 
 * bytes 
 *  1st byte - Static protocol value always set to 0xAA
 *  2nd byte - The device number
 *  3rd byte - The command to set target it is 0x10
 *  4th byte - The channel
 *  5th byte - The data first byte
 *  6th byte - The data second byte
 *
 * @param target Our target to set represented in 2 byte, with a value of 0-255
 *
 * @throws ExceptionServo If writing to the board fails
 */
void ServoUART::setPhysicalTarget(unsigned short int target)
{
    try
    {
        unsigned short int converted
            = map<unsigned short int>(target, 0, 255, SERVO_LOW, SERVO_HIGH);

        unsigned char command[6];
        command[0] = 0xAA;
        command[1] = 0xC;
        command[2] = 0x04;
        command[3] = this->channel;

        // Given an integer needs to be crammed into 2 bytes, with there MSB
        // Set to 0, we need to use 
        //    target & 01111111; to zero our MSB
        // 
        // Then shift the remaining bits and AND by 127
        //       (101010101 >> 7) & 011111111
        // Given us a 2 byte target number with there MSB cleared.
        command[4] = converted & 127;
        command[5] = (converted >> 7) & 127;

        if (write(*this->fd, command, sizeof(command)) == -1)
            throw ExceptionServo("ServoUART::setTarget write failed");
    }
    catch (ExceptionInvalidValue e)
    {
        throw ExceptionServo(
            "Invalid setTarget(" + dashee::itostr(target) + ")"
        );
    }
}

/**
 * Get the target value.
 *
 * This command gets the target of a given channel.
 * To do this however we first need to write to the servo telling it that we 
 * want the target value, of our given `channel`. We then read from the board, 
 * which returns the value in a 2 bytes which in collation represent one number.
 * 
 * The value's returned can range from 992 - 8000
 * 
 * The command to tell the servo that we want channel number requires four bytes
 *  1st byte - Static protocol value always set to 0xAA
 *  2nd byte - The device number
 *  3rd byte - The command to set target it is 0x10
 *  4th byte - The channel
 *
 * @throws ExceptionServo If a read write error occurs
 *
 * @returns The Target value of a channel
 */
unsigned short int ServoUART::getPhysicalTarget()
{
    unsigned char command[4];
    command[0] = 0xAA;
    command[1] = 0xC;
    command[2] = 0x10;
    command[3] = this->channel;

    if(write(*this->fd, command, sizeof(command)) == -1)
        throw ExceptionServo("ServoUART::getTarget write failed");

    unsigned char response[2];
    
    // Go through and read each byte by byte
    for (int n = 0, total = 0; n < 2; total++)
    {
        if (total > 10)
            throw ExceptionServo("Reading getError, ran more than 10 times");

        int ec = read(*this->fd, response+n, 1);

        // the ec came back with read error, lets not continue
        if(ec < 0)
            throw ExceptionServo("read failed in ServoUART::getTarget");

        // the ec came back with 0, which means sleep and try again
        if (ec == 0)
            continue;
        
        // nth response was set, lets set the next one
        n++;
    }

    unsigned short int target = response[0] + 256*response[1];
    if (target == 0)
	target = SERVO_LOW;

    return map<unsigned short int>(
	target,
        SERVO_LOW, 
        SERVO_HIGH,
        0, 
        255
    );
}

/**
 * Destructor.
 *
 * Does nothing.
 */
ServoUART::~ServoUART()
{
}
