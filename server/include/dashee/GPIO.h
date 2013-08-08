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

    const int HIGH = 1;
    const int LOW = 0;
    
    /**
     * This holds the pin value used by this
     * instance of the class
     */
    int pinNumber;

protected:

public:

    // Set up the GPIO by exporting
    GPIO(int pinNumber);

    // Get the current direction set
    int getDirection();

    // Set the direction
    void setDirection();

    // Toggle the direction setting
    void toggleDirection();

    // write to the GPIO Pin
    int write();

    // write GPIO_HIGH to GPIO
    void high();

    // write GPIO_LOW to GPIO
    void low();

    // toggle high and low
    void toggle();

    // Read from the GPIO
    int read();

    // Kill and unexport from 
    ~GPIO();
}
