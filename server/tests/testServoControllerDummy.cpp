#include "dashee.h"

CPPUNIT_TEST_SUITE_REGISTRATION(dashee::test::ServoControllerDummy);
#include <dashee/Exception/OutOfBounds.h>
#include <dashee/ServoController/Dummy.h>

int main(int argc, char ** argv)
{
    return dashee::test::run(argc, argv);
}
