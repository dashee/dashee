#include "Hardware/Accelerometer/Dummy.h"
#include "dashee.h"

CPPUNIT_TEST_SUITE_REGISTRATION(dashee::test::Hardware::AccelerometerDummy);

int main(int argc, char ** argv)
{
    return dashee::test::run();
}
