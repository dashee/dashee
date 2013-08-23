/**
 * Implement the body of the GPIO class. 
 *
 * @author Shahmir Javaid
 */

#include <dashee/GPIO.h>

using namespace dashee;

/**
 * This will set the pinNumber variable and also set
 * the direction on the GPIO. It also needs to export
 * the GPIO before it can be used
 *
 * @param pin - The pin to set
 * @param direction - The Direction of the Pin to set
 *
 * @throws Exception_GPIO
 */
GPIO::GPIO(unsigned short int pin, char direction)
{
    this->setPin(pin);
    this->exportPin();
    this->setDirection(direction);
}

/**
 * Set the pin value given the parameter. The pin must
 * be greater than 0
 *
 * @param pin
 *
 * @throws Excpetion_GPIO
 */
void GPIO::setPin(unsigned short int pin)
{
    if (pin < 1)
        throw Exception_GPIO("pinNumber must be greater than 0");

    this->pin = pin;
}

/**
 * Gets the value of the pin
 *
 * @return unsigned short - The pin number
 */
unsigned short int GPIO::getPin()
{
    return this->pin;
}

/**
 * The static version of the exportPin function
 * usefull because this class can be static and initiated
 * as the user wishes
 * 
 * Function use to write the pinNumber to the
 * GPIO export for exporting. The export file
 * is in /sys/class/gpio/export
 *
 * @param pin - The pin to export
 *
 * @throw Exception_GPIO
 */
void GPIO::exportPin(int pin)
{
    const char * file = "/sys/class/gpio/export";

    if (!dashee::Common::fexists(file))
        throw Exception_GPIO("File '" + (std::string)file + "' does not exist!");
    
    int fd = ::open(file, O_WRONLY);
    if (fd == -1)
        throw Exception_GPIO("File '" + (std::string)file + "' failed to open!");

    char buffer[3];
    ssize_t bytesToWrite = sprintf(buffer, "%d", pin);
    if (::write(fd, buffer, bytesToWrite) == -1)
        throw Exception_GPIO("Write failed for file '" + (std::string)file + "'!");

    ::close(fd);
}

/**
 * Call the static instance with the initiated
 * pin number as the parameter.
 */
void GPIO::exportPin()
{
    GPIO::exportPin(this->pin);
}

/**
 * Function to unexport the current pin.
 * Revert to the export function, this writes to the 
 * unexport file in /sys/class/gpio/unexportd
 *
 * @param pin - The pin number to unexport
 *
 * @throw Exception_GPIO
 */
void GPIO::unexportPin(int pin)
{
    const char * file = "/sys/class/gpio/unexport";

    if (!dashee::Common::fexists(file))
        throw Exception_GPIO("File '" + (std::string)file + "' does not exist!");
    
    int fd = ::open(file, O_WRONLY);
    if (fd == -1)
        throw Exception_GPIO("File '" + (std::string)file + "' failed to open!");

    char buffer[3];
    ssize_t bytesToWrite = ::sprintf(buffer, "%d", pin);
    if (::write(fd, buffer, bytesToWrite) == -1)
        throw Exception_GPIO("Write failed for file '" + (std::string)file + "'!");

    ::close(fd);
}

/**
 * Call the static instance with the initiated
 * pin number as the parameter.
 */
void GPIO::unexportPin()
{
    GPIO::unexportPin(this->pin);
}

/**
 * This will set the direction to the given direction
 * in the parameter. To set a direction it is presumed that you
 * have exported the GPIO and the file that relates to the GPIO pin 
 * exists.
 *
 * @param pin - The pin value to set the direction of
 * @param direction - The Direction of the Pin to set
 *
 * @throws Exception_GPIO
 */
void GPIO::setDirection(int pin, char direction)
{
    char file[100];
    ::snprintf(file, 100, "/sys/class/gpio/gpio%d/direction", pin);

    if (!dashee::Common::fexists(file))
        throw Exception_GPIO("File '" + (std::string)file + "' does not exist!");

    int fd = ::open(file, O_WRONLY);
    if (fd == -1)
        throw Exception_GPIO("File '" + (std::string)file + "' failed to open!");

    char buffer[3];
    ssize_t bytesToWrite;

    if (direction == dashee::GPIO::IN)
        bytesToWrite = ::sprintf(buffer, "%s", "in");
    else if(direction == dashee::GPIO::OUT)
        bytesToWrite = ::sprintf(buffer, "%s", "out");
    else
        throw Exception_GPIO("Value must be only IN or OUT in GPIO::setDirection");

    if (::write(fd, buffer, bytesToWrite) == -1)
        throw Exception_GPIO("Write failed for file '" + (std::string)file + "'!");

    ::close(fd);
}

/**
 * Call the static function of this initiated
 * class with pin as the added parameter
 *
 * @param direction - The direction of the pin to set
 */
void GPIO::setDirection(char direction)
{
    GPIO::setDirection(this->pin, direction);
}

/**
 * Returns the value of the direction set
 * the valua is usually "out" or "in" the 
 * function converts this to 'o' or 'i' respectively
 *
 * @returns char - HIGH/LOW
 *
 * @throws Exception_GPIO
 */
char GPIO::getDirection(int pin)
{
    char file[100];
    ::snprintf(file, 100, "/sys/class/gpio/gpio%d/direction", pin);

    if (!dashee::Common::fexists(file))
        throw Exception_GPIO("File '" + (std::string)file + "' does not exist!");

    int fd = ::open(file, O_WRONLY);
    if (fd == -1)
        throw Exception_GPIO("File '" + (std::string)file + "' failed to open!");

    char value[3];
    if (::read(fd, value, 3) < 0) 
        throw Exception_GPIO("Failed to read file '" + (std::string)file + "'!");

    ::close(fd);

    if (::strncmp(value, (const char *)dashee::GPIO::OUT, 1) == 0)
        return dashee::GPIO::OUT;
    else if (::strncmp(value, (const char *)dashee::GPIO::IN, 1) == 0)
        return dashee::GPIO::IN;
    else
        throw Exception_GPIO("Unknown direction value");
}

/**
 * Calls the static version with the initiated pin number
 * of this initiated class
 *
 * @returns char - HIGH/LOW
 */
char GPIO::getDirection()
{
    return GPIO::getDirection(this->pin);
}

/**
 * Write a value to the ping, driving it high 1, or low 0
 * The value is only valid if it is HIGH or LOW as defined by the class
 *
 * @param pin - The value of the pin
 * @param value - The value to set
 *
 * throw Exception_GPIO
 */
void GPIO::write(int pin, unsigned short int value)
{
    char file[100];
    ::snprintf(file, 100, "/sys/class/gpio/gpio%d/value", pin);

    if (!dashee::Common::fexists(file))
        throw Exception_GPIO("File '" + (std::string)file + "' does not exist!");

    int fd = ::open(file, O_WRONLY);
    if (fd == -1)
        throw Exception_GPIO("File '" + (std::string)file + "' failed to open!");

    char buffer[3];
    ssize_t bytesToWrite;

    if (value == dashee::GPIO::HIGH || value == dashee::GPIO::LOW)
        bytesToWrite = ::sprintf(buffer, "%d", value);
    else
        throw Exception_GPIO("Value must be only HIGHT or LOW in GPIO::write");

    if (::write(fd, buffer, bytesToWrite) == -1)
        throw Exception_GPIO("Write failed for file '" + (std::string)file + "'!");

    ::close(fd);
}

/**
 * Call the static version with the initiated pin value
 *
 * @param value - The value to set
 */
void GPIO::write(unsigned short int value)
{
    GPIO::write(this->pin, value);
}

/**
 * Drive the GPIO HIGH
 */
void GPIO::high()
{
    this->write(dashee::GPIO::HIGH);
}

/**
 * Drive the GPIO LOW
 */
void GPIO::low()
{
    this->write(dashee::GPIO::LOW);
}

/**
 * This lets you read the value of a given pin
 * and return its value in int
 *
 * @param pin - The pin to read from
 *
 * @returns int - The value of the Pin
 *
 * @throws Exception_GPIO
 */
int GPIO::read(int pin)
{
    char file[100];
    ::snprintf(file, 100, "/sys/class/gpio/gpio%d/value", pin);

    if (!dashee::Common::fexists(file))
        throw Exception_GPIO("File '" + (std::string)file + "' does not exist!");

    int fd = ::open(file, O_WRONLY);
    if (fd == -1)
        throw Exception_GPIO("File '" + (std::string)file + "' failed to open!");

    char value[3];
    if (::read(fd, value, 3) < 0) 
        throw Exception_GPIO("Failed to read file '" + (std::string)file + "'!");

    ::close(fd);

    return dashee::Common::strtol(value);
}

/**
 * Call the static version with the initiated
 * pin number
 *
 * @returns int - The value of the Pin
 */
int GPIO::read()
{
    return GPIO::read(this->pin);
}

/**
 * Cleanup and unexport
 */ 
GPIO::~GPIO()
{
    this->unexportPin();
}