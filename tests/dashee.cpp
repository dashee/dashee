#include "dashee.h"

/**
 * Run the REGISTERED test SUITE
 *
 * @returns An integer suggesting test status
 * @retval 1 Test failed
 * @retval 0 Test Passed
 */
int dashee::test::run()
{
    CPPUNIT_NS::TestResult testresult;
    CPPUNIT_NS::TestRunner runner;
    CPPUNIT_NS::TestFactoryRegistry &registry = CPPUNIT_NS::TestFactoryRegistry::getRegistry();

    // register listener for collecting the test-results
    CPPUNIT_NS::TestResultCollector collectedresults;
    testresult.addListener(&collectedresults);

    runner.addTest(registry.makeTest());
    runner.run(testresult);

    // Print test in a compiler compatible format.
    CppUnit::CompilerOutputter outputter( &collectedresults, std::cerr );
    outputter.write(); 
    
    return collectedresults.wasSuccessful() ? 0 : 1;
}
