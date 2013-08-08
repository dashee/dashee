/**
 * This class is designed to run GPIO functions, each instance
 * of the class represents each instance of used pin
 *
 * An instance will export a GPIO ping and on close unexport the value
 * You can change directions of the given pin and read/write to the pin
 *
 * @author Shahmir Javaid
 */

#ifndef DASHEE_GPIO_H
#define DASHEE_GPIO_H

#include <dashee/Exception/GPIO.h>

namespace dashee
{
    class GPIO;
}

class dashee::GPIO
{

private:

    /** 
     * Constant values used for 
     * High and Low definitions
     */
    const int HIGH = 1;
    const int LOW = 0;

    /**
     * Constant to represent the In or Out
     * direction of the GPIO Pin
     */
    const char IN = 'i';
    const char OUT = 'o';
    
    /**
     * This holds the pin value used by this
     * instance of the class
     */
    int pinNumber;

protected:

public:

    // Set up the GPIO by exporting
    GPIO(int pinNumber, char direction);

    // Get the current direction set
    char getDirection();

    // Set the direction
    void setDirection(char direction);

    // Set the value of the Pin
    void setPin(int pinNumber);

    // Get the value of the Pin
    int getPin();

    // write to the GPIO Pin
    void write(int value);

    // write high to the GPIO Pin
    void high();

    // write low to the GPIO Pin
    void low();

    // Read from the GPIO
    int read();

    // Kill and unexport from 
    ~GPIO();
}

#endif
