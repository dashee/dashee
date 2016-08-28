#include "GPIO.h"

using namespace dashee::test;

/**
 * Start up
 */ 
void GPIO::setUp()
{
    this->gpio = new dashee::GPIO(22, dashee::GPIO::OUT);
}

/**
 * Simple test which checks wheather or not the file
 * is 
 */
void GPIO::testExportAndUnexport()
{
    CPPUNIT_ASSERT(dashee::fexists("/sys/class/gpio/gpio22"));

    CPPUNIT_ASSERT(dashee::fexists("/sys/class/gpio/gpio23") == false);
    dashee::GPIO::exportPin(23);
    CPPUNIT_ASSERT(dashee::fexists("/sys/class/gpio/gpio23"));
    dashee::GPIO::unexportPin(23);
    CPPUNIT_ASSERT(dashee::fexists("/sys/class/gpio/gpio23") == false);
}

/**
 * Test the direction setters and getters
 */
void GPIO::testSetAndGetDirection()
{
    CPPUNIT_ASSERT(this->gpio->getDirection() == dashee::GPIO::OUT);
    this->gpio->setDirection(dashee::GPIO::IN);
    CPPUNIT_ASSERT(this->gpio->getDirection() == dashee::GPIO::IN);

    dashee::GPIO::exportPin(23);
    dashee::sleep(150000);
    dashee::GPIO::setDirection(23, dashee::GPIO::OUT);
    CPPUNIT_ASSERT(dashee::GPIO::getDirection(23) == dashee::GPIO::OUT);
    dashee::GPIO::setDirection(23, dashee::GPIO::IN);
    CPPUNIT_ASSERT(dashee::GPIO::getDirection(23) == dashee::GPIO::IN);
    dashee::GPIO::unexportPin(23);
}

/**
 * Test read and write to the gpio pin
 */
void GPIO::testReadAndWrite()
{
    this->gpio->write(1);
    CPPUNIT_ASSERT(this->gpio->read() == dashee::GPIO::HIGH);
    this->gpio->write(0);
    CPPUNIT_ASSERT(this->gpio->read() == dashee::GPIO::LOW);
}

/**
 * Test setting the pin High and Low
 */ 
void GPIO::testHighAndLow()
{
    this->gpio->high();
    CPPUNIT_ASSERT(this->gpio->read() == dashee::GPIO::HIGH);
    this->gpio->low();
    CPPUNIT_ASSERT(this->gpio->read() == dashee::GPIO::LOW);
}

/**
 * The class is designed to ignore double exporting files which already exist
 *
 * This test just makes sure that we don't through an exception
 */
void GPIO::testDoubleExportUnExportIsOK()
{
    dashee::GPIO::exportPin(22);
    CPPUNIT_ASSERT(true);
}

/**
 * Check the value of the current pin
 */
void GPIO::testGetPin()
{
    CPPUNIT_ASSERT(this->gpio->getPin());
}

/**
 * Pin value 0 is nonsense 
 */
void GPIO::testInvalidPinValue()
{
    dashee::GPIO x(0, dashee::GPIO::OUT);
}

/**
 * Ensure reading an invalid pin throws an exception
 */
void GPIO::testInvalidReadPin()
{
    dashee::GPIO::read(23);
}

/**
 * Test invalid write
 */
void GPIO::testInvalidWritePin()
{
    dashee::GPIO::write(23, 1);
}

/**
 * Clean up
 */
void GPIO::tearDown()
{
    delete this->gpio;
}
