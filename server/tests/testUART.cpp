#include "Servo/UART.h"
#include "ServoController/UART.h"
#include "dashee.h"

CPPUNIT_TEST_SUITE_REGISTRATION(dashee::test::ServoUART);
CPPUNIT_TEST_SUITE_REGISTRATION(dashee::test::ServoControllerUART);

int main()
{
    return dashee::test::run();
}
