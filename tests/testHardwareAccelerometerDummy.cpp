#include "Hardware/Accelerometer/Dummy.h"
#include "dashee.h"

CPPUNIT_TEST_SUITE_REGISTRATION(dashee::test::Hardware::AccelerometerDummy);

int main()
{
    return dashee::test::run();
}
