#include <dashee/I2C.h>

using namespace dashee;

/**
 * Initialize our I2C class with the given dev Number, the filepath is prefixed 
 * using I2C::DEVICE_PREFIX
 *
 * @param devNumber The number of the I2C device to open
 */
I2C::I2C(const int devNumber)
{
    std::string device = DEVICE_PREFIX + dashee::itostr(devNumber);
    this->init(device);
}

/**
 * Initialize our I2C class with the given dev file path
 *
 * @param filePath The device file path
 */
I2C::I2C(const std::string filePath)
{
    this->init(filePath);
}

/**
 * Initialize function used by our constructors.
 *
 * Open a handle to the device
 */
void I2C::init(const std::string dev)
{
    // Open the device
    this->fd = open(dev.c_str(), O_RDWR | O_NOCTTY);
    if (this->fd == -1)
        throw ExceptionI2C("Failed opening I2C device '" + dev + "'.");

    // Initialize and Reset the buffer
    this->buffer = new char[100];
    memset(this->buffer, 0, sizeof(*this->buffer) * 100);
}

/**
 * Close the device
 */
I2C::~I2C()
{
    close(this->fd);
    delete[] this->buffer;
}

// This variable specifies the prefix to use when constructing with an int value
// see I2C::I2C(int) for usage.
const std::string dashee::I2C::DEVICE_PREFIX = "/dev/i2c-";
