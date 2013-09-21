#include <cppunit/TestFixture.h>
#include <cppunit/TestCase.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestResultCollector.h>

#include <dashee/Common.h>
#include <dashee/Log.h>
#include <dashee/Exception/OutOfBounds.h>
#include <dashee/ServoController/Dummy.h>

class ServoControllerDummyTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(ServoControllerDummyTest);
    CPPUNIT_TEST_EXCEPTION(testInvalidFile, dashee::ExceptionServoController);
    CPPUNIT_TEST_EXCEPTION(testInvalidChannel, dashee::ExceptionOutOfBounds);
    CPPUNIT_TEST_EXCEPTION(testInvalidPositiveTarget, dashee::ExceptionServo);
    CPPUNIT_TEST_EXCEPTION(testInvalidNegativeTarget, dashee::ExceptionServo);
    CPPUNIT_TEST_EXCEPTION(testInvalidLargePositiveTarget, dashee::ExceptionServo);
    CPPUNIT_TEST_EXCEPTION(testInvalidLargeNegativeTarget, dashee::ExceptionServo);
    CPPUNIT_TEST(testSetAndGetServoTarget);
    CPPUNIT_TEST(testFallbackAndRevertTarget);
    CPPUNIT_TEST_SUITE_END();

private:
    dashee::ServoControllerDummy * servoController;

protected:
    void testInvalidFile();
    void testInvalidChannel();
    void testInvalidPositiveTarget();
    void testInvalidNegativeTarget();
    void testInvalidLargePositiveTarget();
    void testInvalidLargeNegativeTarget();
    void testSetAndGetServoTarget();
    void testFallbackAndRevertTarget();

public:
    virtual void setUp();
    void tearDown();
};

/**
 * Start up
 */ 
void ServoControllerDummyTest::setUp()
{
    this->servoController = new dashee::ServoControllerDummy("data/Servo.bin", 6);
}

/**
 * Catch an exception when an invalid file is called
 */
void ServoControllerDummyTest::testInvalidFile()
{
    this->servoController = new dashee::ServoControllerDummy("poop", 6);
}

/**
 * Exception is thrown when the channel is invalid
 */
void ServoControllerDummyTest::testInvalidChannel()
{
    this->servoController->setTarget(100, 2);
}

/**
 * Exception is thrown when the target is invalid
 */
void ServoControllerDummyTest::testInvalidPositiveTarget()
{
    this->servoController->setTarget(1, 1000);
}

/**
 * Exception is thrown when the target is invalid
 */
void ServoControllerDummyTest::testInvalidNegativeTarget()
{
    this->servoController->setTarget(1, -1000);
}

/**
 * Exception is thrown when the target is invalid and set to a 
 * very very large number
 */
void ServoControllerDummyTest::testInvalidLargePositiveTarget()
{
    this->servoController->setTarget(1, 100084);
}

/**
 * Exception is thrown when the target is invalid and set to a 
 * very very large negative number
 */
void ServoControllerDummyTest::testInvalidLargeNegativeTarget()
{
    this->servoController->setTarget(1, -234128989934832);
}

/**
 * This test will set the Servo Value, and see if the 
 * get value is correct
 */
void ServoControllerDummyTest::testSetAndGetServoTarget()
{
    for (unsigned short int servos = 0; servos < 6; servos++) 
    {
        for (unsigned short int x = 0; x <= 100; x++)
        {
            this->servoController->setTarget(servos, x);
            CPPUNIT_ASSERT(this->servoController->getTarget(servos) == x);
        }
    }
}

/**
 * Test and see weather fallbacks worked or not
 */ 
void ServoControllerDummyTest::testFallbackAndRevertTarget()
{
    // Call revert without any reason, just to see all works
    this->servoController->revert();

    // Call fallback without any reason to make sure no exceptions are 
    // thrown
    this->servoController->fallback();
        
    // set initial positions to something unique
    this->servoController->setTarget(0, 5);
    this->servoController->setTarget(1, 5);
    this->servoController->setTarget(2, 5);
    this->servoController->setTarget(3, 5);
    this->servoController->setTarget(4, 5);
    this->servoController->setTarget(5, 5);

    // Check to ensure that initial positions are valid
    CPPUNIT_ASSERT(this->servoController->getTarget(0) == 5);
    CPPUNIT_ASSERT(this->servoController->getTarget(1) == 5);
    CPPUNIT_ASSERT(this->servoController->getTarget(2) == 5);
    CPPUNIT_ASSERT(this->servoController->getTarget(3) == 5);
    CPPUNIT_ASSERT(this->servoController->getTarget(4) == 5);
    CPPUNIT_ASSERT(this->servoController->getTarget(5) == 5);
    
    // Set the fallbacks
    this->servoController->setTargetFallback(0, 10);
    this->servoController->setTargetFallback(1, 20);
    this->servoController->setTargetFallback(2, 30);
    this->servoController->setTargetFallback(3, 40);
    this->servoController->setTargetFallback(4, 50);
    this->servoController->setTargetFallback(5, 60);

    // Run and check fallback and see weather it worked
    this->servoController->fallback();
    CPPUNIT_ASSERT(this->servoController->getTarget(0) == 10);
    CPPUNIT_ASSERT(this->servoController->getTarget(1) == 20);
    CPPUNIT_ASSERT(this->servoController->getTarget(2) == 30);
    CPPUNIT_ASSERT(this->servoController->getTarget(3) == 40);
    CPPUNIT_ASSERT(this->servoController->getTarget(4) == 50);
    CPPUNIT_ASSERT(this->servoController->getTarget(5) == 60);

    // Run and cheack weather the reverting of the servo worked
    this->servoController->revert();
    CPPUNIT_ASSERT(this->servoController->getTarget(0) == 5);
    CPPUNIT_ASSERT(this->servoController->getTarget(1) == 5);
    CPPUNIT_ASSERT(this->servoController->getTarget(2) == 5);
    CPPUNIT_ASSERT(this->servoController->getTarget(3) == 5);
    CPPUNIT_ASSERT(this->servoController->getTarget(4) == 5);
    CPPUNIT_ASSERT(this->servoController->getTarget(5) == 5);
    
    // Call revert unnesesorily and make sure the values dont budge
    this->servoController->setTarget(0, 99);
    this->servoController->setTarget(1, 99);
    this->servoController->setTarget(2, 99);
    this->servoController->setTarget(3, 99);
    this->servoController->setTarget(4, 99);
    this->servoController->setTarget(5, 99);
    this->servoController->revert();
    CPPUNIT_ASSERT(this->servoController->getTarget(0) == 99);
    CPPUNIT_ASSERT(this->servoController->getTarget(1) == 99);
    CPPUNIT_ASSERT(this->servoController->getTarget(2) == 99);
    CPPUNIT_ASSERT(this->servoController->getTarget(3) == 99);
    CPPUNIT_ASSERT(this->servoController->getTarget(4) == 99);
    CPPUNIT_ASSERT(this->servoController->getTarget(5) == 99);
}

/**
 * Clean up
 */
void ServoControllerDummyTest::tearDown()
{
    delete this->servoController;
}

CPPUNIT_TEST_SUITE_REGISTRATION(ServoControllerDummyTest);

int main(int argc, char ** argv)
{
    // Load the data file
    char * datafile = (char *)"data/Servo.bin";
    if (argc == 1)
        datafile = argv[0]; 

    // If the file does not exist, bomb out and return to user
    // with an error
    if (!dashee::Common::fexists(datafile))
    {
        dashee::Log::error("Data file '%s' does not exist!", datafile);
        return 2;
    }

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
