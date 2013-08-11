#include <cppunit/TestFixture.h>
#include <cppunit/TestCase.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestResultCollector.h>

#include <include/dashee/GPIO.h>

class GPIOTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(ServoControllerDummyTest);
    //CPPUNIT_TEST_EXCEPTION(testInvalidFile, Exception_);
    //CPPUNIT_TEST(testSetAndGetServoTarget);
    CPPUNIT_TEST_SUITE_END();

private:
    dashee::GPIO * gpio;

protected:
    void testExport();

public:
    void setUp();
    void tearDown();
};

/**
 * Start up
 */ 
void GPIOTest::setUp()
{
}

/**
 * Simple test which checks wheather or not the file
 * is 
 */
void GPIOTest::testExport()
{
    
}

/**
 * Clean up
 */
void GPIOTest::tearDown()
{
}

CPPUNIT_TEST_SUITE_REGISTRATION(GPIOTest);

int main(int argc, char ** argv)
{
    CPPUNIT_NS::TestResult testresult;
    CPPUNIT_NS::TestRunner runner;
    CPPUNIT_NS::TestFactoryRegistry &registry = CPPUNIT_NS::TestFactoryRegistry::getRegistry();

    // register listener for collecting the test-results
    CPPUNIT_NS::TestResultCollector collectedresults;
    testresult.addListener(&collectedresults);

    runner.addTest(registry.makeTest());
    runner.run(testresult);
    
    return collectedresults.wasSuccessful() ? 0 : 1;
}
