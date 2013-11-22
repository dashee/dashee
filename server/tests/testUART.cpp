#include "Servo/UART.h"
#include "ServoController/UART.h"
#include "dashee.h"

CPPUNIT_TEST_SUITE_REGISTRATION(dashee::test::ServoUART);
CPPUNIT_TEST_SUITE_REGISTRATION(dashee::test::ServoControllerUART);

int main(int argc, char ** argv)
{
    return dashee::test::run();
}
