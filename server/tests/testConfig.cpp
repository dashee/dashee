#include "Config.h"
#include "dashee.h"

CPPUNIT_TEST_SUITE_REGISTRATION(dashee::test::Config);

int main(int argc, char ** argv)
{
    try
    {
        if (argc != 2)
            throw dashee::Exception("Must provide 1 argument for directory");

        // Set the directory path
        dashee::test::Config::directoryPath = argv[1];

        return dashee::test::run();
    }
    catch(dashee::Exception e)
    {
	fprintf(stderr, "Exception: %s\n", e.what());
    }

    return -1;
}
