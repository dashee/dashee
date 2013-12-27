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
		"Setting 10bit address flag failed ioctl came back with '" + 
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
    const ssize_t ec = ::write(this->fd, commands, 1);

    if (ec != 1)
	throw ExceptionI2C(
		"Setting working register '" + dashee::itostr(reg) + 
		"' failed. Exit code: " + dashee::itostr(ec)
	    );
}

/**
 * Read bytes for the working register and store it in the buffer. 
 *
 * We always operate on the 0th element of the vector, so existing values
 * will be overwritten.
 *
 * @param reg The register to read
 * @param buffer The buffer to write to from reading values
 * @param numOfBytes the number of bytes to read
 *
 * @throws ExceptionNullPointer If buffer is null
 * @throws ExceptionI2C If numOfBytes is 0
 * @throws ExceptionI2C If read fails
 */
void I2C::read(
	const unsigned char reg,
	std::vector<unsigned char> * const buffer, 
	const size_t numOfBytes
    )
{
    if (numOfBytes == 0)
	throw ExceptionI2C("Trying to read 0 bytes, why?");

    if (buffer == NULL)
	throw ExceptionNullPointer("Buffer was NULL in I2C::read");

    // Set register and resize the buffer if needed
    this->setWorkingRegister(reg);

    // Number of bytes are greater so resize the buffer
    if (numOfBytes > buffer->size())
	buffer->resize(numOfBytes, 0x00);

    const ssize_t ec 
	= ::read(this->fd, &buffer->operator[](0), numOfBytes);
    if (ec != static_cast<ssize_t>(numOfBytes))
	throw ExceptionI2C(
		"Read failed in for register '" + 
		dashee::itostr(reg) + 
		"', The number of bytes " + "returned(" + 
		dashee::itostr(ec) + ") were less than the" + 
		" bytes expected(" + dashee::itostr(numOfBytes) + ")."
	    );
}

/**
 * Read from register and store it in the buffer. The number of bytes
 * read is the size of the register
 *
 * @param reg
 * @param buffer The buffer to read, the size determine the number of bytes read
 */
void I2C::read(
	const unsigned char reg,
	std::vector<unsigned char>* const buffer
    )
{
    this->read(reg, buffer, buffer->size());
}

/**
 * Write to the register the values, given by buffer
 *
 * @param reg The register to write to
 * @param buffer The buffer to read the bytes to write
 * @param numOfBytes The number of bytes to write
 */
void I2C::write(
	const unsigned char reg, 
	const std::vector<unsigned char> * buffer,
	const size_t numOfBytes
    )
{
    if (numOfBytes == 0)
	throw ExceptionI2C("Trying to write 0 bytes, why?");

    if (buffer == NULL)
	throw ExceptionNullPointer("Buffer was NULL in I2C::read");

    // Make sure the number of bytes written are smaller or equal to the size
    // of the buffer
    if (numOfBytes > buffer->size())
	throw ExceptionOutOfBounds(
		"The buffer is smaller than the number of bytes which are "
		"being written to the device"
	    );

    // Create a temporary buffer, which copies the buffer, and inserts a 
    // register at the start
    std::vector<unsigned char> temp(*buffer);
    temp.insert(temp.begin(), reg);
    
    const ssize_t ec = ::write(this->fd, &temp[0], numOfBytes+1);

    if (ec != static_cast<ssize_t>(numOfBytes+1))
	throw ExceptionI2C(
		"Failed writing " + dashee::itostr(numOfBytes) + 
		" bytes to register '" + dashee::itostr(reg) + 
		"' failed. Exit code: " + dashee::itostr(ec)
	    );
}

/**
 * Shorthand for the full write, where the size is assumed to be the size
 * of the vector array
 *
 * @param reg The register to write to
 * @param buffer the buffer to read the bytes to be written
 */
void I2C::write(
	const unsigned char reg, 
	const std::vector<unsigned char> * buffer
    )
{
    this->write(reg, buffer, buffer->size());
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
