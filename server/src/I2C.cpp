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

    // Set the 10 bit address flag to false
    this->set10BitAddress(false);

    // Set our slave value
    this->setSlaveAddress(slaveAddress);

    // Set the working register to 0x00
    this->workingRegister = 0x00;
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

    // No point continuing as the slave address is the same
    // as the current set one
    if (this->slaveAddress == slaveAddress)
	return;

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
 * This will write one byte to our I2C device and by chance setting the 
 * register value
 *
 * @param reg the Register to set
 *
 * @throws ExceptionI2C If write return non 1
 */ 
void I2C::setWorkingRegister(const unsigned char reg)
{
    // Tell the device we will read from the reg register
    const unsigned char commands[1] = { reg };
    const ssize_t ec = write(this->fd, commands, 1);

    if (ec != 1)
	throw ExceptionI2C(
		"Setting working register '" + dashee::itostr(reg) + 
		"' failed. Exit code: " + dashee::itostr(ec)
	    );

    this->workingRegister = reg;
}

/**
 * Get the value of the current working register.
 *
 * @return The value of the current working register
 */
unsigned char I2C::getWorkingRegister() const
{
    return this->workingRegister;
}

/**
 * Read from a specific register.
 *
 * The steps to read from a register is to write a register value to the
 * I2C device telling it we will now read from this buffer, and then call
 * read.
 *
 * @param reg The register to read from
 * @param numOfBytes The number of bytes to read
 */
std::vector<unsigned char> I2C::readFromRegister(
	const unsigned char reg, 
	const size_t numOfBytes
    )
{
    // Set the working register.
    this->setWorkingRegister(reg);
    // Tell the device we will read from the reg register

    std::vector<unsigned char> buffer;
    buffer.resize(numOfBytes);

    const ssize_t ec = ::read(this->fd, &buffer[0], numOfBytes);
    if (ec != static_cast<ssize_t>(numOfBytes))
	throw ExceptionI2C(
		"Read failed in for register '" + dashee::ctostr(reg) + 
		"', The number of bytes " + "returned(" + 
		dashee::itostr(ec) + ") were less than the" + 
		" bytes expected(" + dashee::itostr(numOfBytes) + ")."
	    );

    return buffer;
}

/**
 * Read bytes for the working register. 
 *
 * Unlike readFromRegister the read function does not tell the device about
 * the register it is reading from, it presumes that the read values are coming
 * from the last working register.
 *
 * @param numOfBytes the number of bytes to read
 */
std::vector<unsigned char> I2C::read(const size_t numOfBytes)
{
    std::vector<unsigned char> buffer;
    buffer.resize(numOfBytes);

    const ssize_t ec = ::read(this->fd, &buffer[0], numOfBytes);
    if (ec != static_cast<ssize_t>(numOfBytes))
	throw ExceptionI2C(
		"Read failed in for register '" + 
		dashee::itostr(this->workingRegister) + 
		"', The number of bytes " + "returned(" + 
		dashee::itostr(ec) + ") were less than the" + 
		" bytes expected(" + dashee::itostr(numOfBytes) + ")."
	    );

    return buffer;
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
