#include "Hardware/Servo/UART.h"

using namespace dashee::test::Hardware;

/**
 * Create a new instance of ServoControllerDummy and 
 * set it to the private variable
 */
void ServoUART::setUp()
{
    this->fd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY);

    if (this->fd == -1)
        CPPUNIT_FAIL("Cannot open file!");
    
    struct termios options;
    tcgetattr(this->fd, &options);
    cfsetispeed(&options, B230400);
    cfsetospeed(&options, B230400);

    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;

    // no flow control
    options.c_cflag &= ~CRTSCTS;

    options.c_cflag |= CREAD | CLOCAL;  // turn on READ & ignore ctrl lines
    options.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl

    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
    options.c_oflag &= ~OPOST; // make raw

    // see: http://unixwiz.net/techtips/termios-vmin-vtime.html
    options.c_cc[VMIN]  = 0;
    options.c_cc[VTIME] = 10;

    if (tcsetattr(this->fd, TCSANOW, &options) < 0)
        CPPUNIT_FAIL("Initilizing UART failed");
    
    // Reset the GPIO pin
    dashee::GPIO gpio(18, dashee::GPIO::OUT);
    gpio.low();
    gpio.high();

    // Important 
    dashee::sleep(10000);

    this->servo = new dashee::Hardware::ServoUART(&this->fd, 2);
}

/**
 * TearDown the opened variables and call parent
 * teardown functions
 */
void ServoUART::tearDown()
{
    Servo::tearDown();

    if (this->fd != -1)
        close(this->fd);
}
