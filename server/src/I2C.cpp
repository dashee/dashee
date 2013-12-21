#include <dashee/I2C.h>

using namespace dashee;

/**
 * Initialize our I2C class with the given dev Number, the filepath is prefixed 
 * using I2C::DEVICE_PREFIX
 *
 * @param devNumber The number of the I2C device to open
 * @param slaveAddress The address to set the slave device to
 */
I2C::I2C(const int devNumber, const unsigned char slaveAddress)
{
    std::string device = DEVICE_PREFIX + dashee::itostr(devNumber);
    this->init(device, slaveAddress);
}

/**
 * Initialize our I2C class with the given dev file path
 *
 * @param filePath The device file path
 * @param slaveAddress The address to set the slave device to
 */
I2C::I2C(const std::string filePath, const unsigned char slaveAddress)
{
    this->init(filePath, slaveAddress);
}

/**
 * Initialize function used by our constructors.
 *
 * Open a handle to the device
 * @param slaveAddress The address to set the slave device to
 * 
 * @throws ExceptionI2C If opening the device fails
 */
void I2C::init(const std::string dev, const unsigned char slaveAddress)
{
    // Open the device
    this->fd = open(dev.c_str(), O_RDWR | O_NOCTTY);
    if (this->fd == -1)
        throw ExceptionI2C("Failed opening I2C device '" + dev + "'.");

    // Initialize and Reset the buffer
    this->buffer = new char[100];
    memset(this->buffer, 0, sizeof(*this->buffer) * 100);

    // Set the 10 bit address flag to fals
    this->set10BitAddress(false);

    // Set our slave value
    this->setSlaveAddress(slaveAddress);
}

/** 
 * Set the current slave
 *
 * @param slaveAddress The address of the slave
 * 
 * @throws ExceptionI2C If ioctl failed
 */
void I2C::setSlaveAddress(const unsigned char slaveAddress)
{
    if (slaveAddress >= 128)
	throw ExceptionI2C("Slave address must be less than 128");

    int ec = ioctl(this->fd, I2C_SLAVE, slaveAddress);
    if (ec != 0)
	throw ExceptionI2C(
		"Setting slave('" + 
		dashee::itostr(static_cast<unsigned int>(slaveAddress)) + 
		"') failed ioctl cameback with '" + 
		dashee::itostr(ec)  + 
		"'"
	    );

    this->slaveAddress = slaveAddress;
}

/**
 * Return the value of the current slave
 *
 * @return the value of the slave
 */
unsigned char I2C::getSlaveAddress() const
{
    return this->slaveAddress;   
}

/**
 * Set the 10bit address flag using ioctl 
 *
 * @param flag the value to set it to
 *
 * @throws ExceptionI2C If ioctl failed
 */
void I2C::set10BitAddress(const bool flag)
{
    // The C++ Standard (4.2) says, that true == 1 and false == 0 so the below
    // flag cast to int should be safe
    int ec = ioctl(this->fd, I2C_TENBIT, flag);

    if (ec != 0)
	throw ExceptionI2C(
		"Setting 10bit address flag failed ioctl cameback with '" + 
		dashee::itostr(ec)  + 
		"'"
	    );
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
