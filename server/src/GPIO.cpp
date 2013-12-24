#include <dashee/GPIO.h>

using namespace dashee;

/**
 * Construct
 *
 * This will set the pinNumber variable, set the direction on the GPIO
 * and will run export. GPIO cannot handle without exporting so 
 * exporting and later unexporting is important. Once exported setting
 * the direction is also important, although default will be set 
 * according to the manufacturer of the hardware, so it is safe to 
 * set the value that the user require.
 *
 * @param pin The pin to set
 * @param direction The Direction of the Pin to set
 *
 * @throws Exception_GPIO
 */
GPIO::GPIO(unsigned short int pin, char direction)
{
    this->setPin(pin);
    this->exportPin();
    dashee::sleep(90000);
    this->setDirection(direction);
}

/**
 * Set the pin.
 *
 * Set the pin value given the parameter. The pin must
 * be greater than 0
 *
 * @param pin
 *
 * @throws ExcpetionGPIO
 */
void GPIO::setPin(unsigned short int pin)
{
    if (pin < 1)
        throw ExceptionGPIO("pinNumber must be greater than 0");

    this->pin = pin;
}

/**
 * Get the pin.
 *
 * Gets the value of the pin
 *
 * @return The pin number
 */
unsigned short int GPIO::getPin()
{
    return this->pin;
}

/**
 * Export the given pin.
 *
 * The static version of the exportPin function usefull because this class 
 * can be static and initiated as the user wishes. This function is used to 
 * write the pinNumber to the GPIO export for exporting. The export file is
 * in `/sys/class/gpio/export`
 *
 * @param pin The pin to export
 *
 * @throw ExceptionGPIO
 */
void GPIO::exportPin(int pin)
{
    char pinfile[100];
    ::snprintf(pinfile, 100, "/sys/class/gpio/gpio%d/direction", pin);

    if (fexists(pinfile))
        return;

    const char * file = "/sys/class/gpio/export";

    if (!fexists(file))
        throw ExceptionGPIO("File '" + (std::string)file + "' does not exist!");
    
    int fd = ::open(file, O_WRONLY);
    if (fd == -1)
        throw ExceptionGPIO("File '" + (std::string)file + "' failed to open!");

    char buffer[3];
    ssize_t bytesToWrite = sprintf(buffer, "%d", pin);
    if (::write(fd, buffer, bytesToWrite) == -1)
        throw ExceptionGPIO("Write failed for file '" + (std::string)file + "'!");

    ::close(fd);
}

/**
 * Export pin.
 *
 * Call the static instance with the initiated
 * pin number as the parameter.
 */
void GPIO::exportPin()
{
    GPIO::exportPin(this->pin);
}

/**
 * Unexport the given pin.
 *
 * Function to unexport the current pin.
 * Revert to the export function, this writes to the 
 * unexport file in /sys/class/gpio/unexportd
 *
 * @param pin The pin number to unexport
 *
 * @throw Exception_GPIO
 */
void GPIO::unexportPin(int pin)
{
    const char * file = "/sys/class/gpio/unexport";

    if (!fexists(file))
        throw ExceptionGPIO("File '" + (std::string)file + "' does not exist!");
    
    int fd = ::open(file, O_WRONLY);
    if (fd == -1)
        throw ExceptionGPIO("File '" + (std::string)file + "' failed to open!");

    char buffer[3];
    ssize_t bytesToWrite = ::sprintf(buffer, "%d", pin);
    if (::write(fd, buffer, bytesToWrite) == -1)
        throw ExceptionGPIO("Write failed for file '" + (std::string)file + "'!");

    ::close(fd);
}

/**
 * Unexport pin.
 *
 * Call the static instance with the initiated
 * pin number as the parameter.
 */
void GPIO::unexportPin()
{
    GPIO::unexportPin(this->pin);
}

/**
 * Set the direction of the given pin.
 *
 * This will set the direction to the given direction
 * in the parameter. To set a direction it is presumed that you
 * have exported the GPIO and the file that relates to the GPIO pin 
 * exists.
 *
 * @param pin The pin value to set the direction of
 * @param direction The Direction of the Pin to set
 *
 * @throws ExceptionGPIO
 */
void GPIO::setDirection(int pin, char direction)
{
    char file[100];
    ::snprintf(file, 100, "/sys/class/gpio/gpio%d/direction", pin);

    if (!fexists(file))
        throw ExceptionGPIO("File '" + (std::string)file + "' does not exist!");

    int fd = ::open(file, O_WRONLY);
    if (fd == -1)
        throw ExceptionGPIO("File '" + (std::string)file + "' failed to open!");

    char buffer[3];
    ssize_t bytesToWrite;

    if (direction == dashee::GPIO::IN)
        bytesToWrite = ::sprintf(buffer, "%s", "in");
    else if(direction == dashee::GPIO::OUT)
        bytesToWrite = ::sprintf(buffer, "%s", "out");
    else
        throw ExceptionGPIO("Value must be only IN or OUT in GPIO::setDirection");

    if (::write(fd, buffer, bytesToWrite) == -1)
        throw ExceptionGPIO("Write failed for file '" + (std::string)file + "'!");

    ::close(fd);
}

/**
 * Set the direction.
 *  
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
 * Return the direction of the given pin.
 *
 * Returns the value of the direction set
 * the valua is usually `out` or `in` the 
 * function converts this to 'o' or 'i' respectively, or in
 * our terms `IN` or `OUT` constant variables
 * 
 * @param pin The pin number to get the direction of
 *
 * @throws ExceptionGPIO
 *
 * @returns IN/OUT character
 * @retval IN if pin direction is IN
 * @retval OUT if pin direction is OUT
 */
char GPIO::getDirection(int pin)
{
    char file[100];
    ::snprintf(file, 100, "/sys/class/gpio/gpio%d/direction", pin);

    if (!fexists(file))
        throw ExceptionGPIO("File '" + (std::string)file + "' does not exist!");

    int fd = ::open(file, O_WRONLY);
    if (fd == -1)
        throw ExceptionGPIO("File '" + (std::string)file + "' failed to open!");

    char value[3];
    if (::read(fd, value, 3) < 0) 
        throw ExceptionGPIO("Failed to read file '" + (std::string)file + "'!");

    ::close(fd);

    if (::strncmp(value, (const char *)dashee::GPIO::OUT, 1) == 0)
        return dashee::GPIO::OUT;
    else if (::strncmp(value, (const char *)dashee::GPIO::IN, 1) == 0)
        return dashee::GPIO::IN;
    else
        throw ExceptionGPIO("Unknown direction value");
}

/**
 * Get the pin direction.
 *
 * Calls the static version with the initiated pin number
 * of this initiated class
 *
 * @returns IN/OUT character
 * @retval IN if pin direction is IN
 * @retval OUT if pin direction is OUT
 */
char GPIO::getDirection()
{
    return GPIO::getDirection(this->pin);
}

/**
 * Write to the given pin.
 *
 * Write a value to the ping, driving it high 1, or low 0
 * The value is only valid if it is HIGH or LOW as defined by the class
 *
 * @param pin The value of the pin
 * @param value The value to set
 *
 * throw ExceptionGPIO
 */
void GPIO::write(int pin, unsigned short int value)
{
    char file[100];
    ::snprintf(file, 100, "/sys/class/gpio/gpio%d/value", pin);

    if (!fexists(file))
        throw ExceptionGPIO("File '" + (std::string)file + "' does not exist!");

    int fd = ::open(file, O_WRONLY);
    if (fd == -1)
        throw ExceptionGPIO("File '" + (std::string)file + "' failed to open!");

    char buffer[3];
    ssize_t bytesToWrite;

    if (value == dashee::GPIO::HIGH || value == dashee::GPIO::LOW)
        bytesToWrite = ::sprintf(buffer, "%d", value);
    else
        throw ExceptionGPIO("Value must be only HIGHT or LOW in GPIO::write");

    if (::write(fd, buffer, bytesToWrite) == -1)
        throw ExceptionGPIO("Write failed for file '" + (std::string)file + "'!");

    ::close(fd);
}

/**
 * Write to the pin.
 *
 * Call the static version with the initiated pin value
 *
 * @param value The value to set
 */
void GPIO::write(unsigned short int value)
{
    GPIO::write(this->pin, value);
}

/**
 * Set GPIO to high.
 *  
 * Drive the GPIO HIGH
 */
void GPIO::high()
{
    this->write(dashee::GPIO::HIGH);
}

/**
 * Set GPIO to low.
 *
 * Drive the GPIO LOW
 */
void GPIO::low()
{
    this->write(dashee::GPIO::LOW);
}

/**
 * Read from the given pin.
 *
 * This lets you read the value of a given pin
 * and return its value in int
 *
 * @param pin The pin to read from
 *
 * @returns The value of the Pin
 *
 * @throws Exception_GPIO
 */
int GPIO::read(int pin)
{
    char file[100];
    ::snprintf(file, 100, "/sys/class/gpio/gpio%d/value", pin);

    if (!fexists(file))
        throw ExceptionGPIO("File '" + (std::string)file + "' does not exist!");

    int fd = ::open(file, O_WRONLY);
    if (fd == -1)
        throw ExceptionGPIO("File '" + (std::string)file + "' failed to open!");

    char value[3];
    if (::read(fd, value, 3) < 0) 
        throw ExceptionGPIO("Failed to read file '" + (std::string)file + "'!");

    ::close(fd);

    return strtol(value);
}

/**
 * Read from the pin.
 *
 * Call the static version with the initiated
 * pin number.
 *
 * @returns The value of the pin
 */
int GPIO::read()
{
    return GPIO::read(this->pin);
}

/**
 * Destructor.
 *
 * It is important to unexportPin otherwise other programs
 * may think it is being used somewhere else.
 */ 
GPIO::~GPIO()
{
    this->unexportPin();
}
