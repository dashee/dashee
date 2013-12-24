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
 * Unexporting files that do not exist is wrong
 */
void GPIO::testFailUnexportingInvalidFile()
{
    dashee::GPIO::unexportPin(23);
}

/**
 * Clean up
 */
void GPIO::tearDown()
{
    delete this->gpio;
}
