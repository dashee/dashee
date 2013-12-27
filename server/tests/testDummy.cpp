#include "Servo/Dummy.h"
#include "ServoController/Dummy.h"
#include "dashee.h"

CPPUNIT_TEST_SUITE_REGISTRATION(dashee::test::ServoDummy);
CPPUNIT_TEST_SUITE_REGISTRATION(dashee::test::ServoControllerDummy);

int main()
{
    return dashee::test::run();
}
