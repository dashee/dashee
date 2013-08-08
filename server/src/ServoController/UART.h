/**
 * This is a class which handels communications with the Pololu board
 * it is a wrapper over the read and write commands sent to usually /dev/ttyAMA0
 * 
 * The /dev/ttyAMA0 is OS dependant, and be use a later Numerical value if the OS
 * alread has a device running with the similar name
 *
 * The /dev/ttyAMA0 represents the UART protocol, and the pololu board is set to
 * `UART detect baud rate`. However this means the device baud rate is set by the 
 * constructor
 *
 * @author Shahmir Javaid
 */

#ifndef SERVOCONTROLLER_UART_H_
#define SERVOCONTROLLER_UART_H_

#include <termios.h>
#include "../ServoController.h"
#include "../Servo/UART.h"

class ServoControllerUART : public ServoController
{
private:

protected:
        
    /**
     * Given our @dev variable we open this device, which returns the appropriate
     * file handler.
     */
    int fd;
    
    // Reset our board by driving the reset pin low
    void reset();
    
    // Initialize our board
    void init();
    
public:
    // Open our device, and set our @servos array
    explicit ServoControllerUART(const char *, const unsigned short int = 8);
    
    // Get the error from the board
    virtual short int getError();
    
    // Close the device
    virtual ~ServoControllerUART();
};

#endif
