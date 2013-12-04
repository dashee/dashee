/**
 * @file tests/GPIO.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_TEST_GPIO_H_
#define DASHEE_TEST_GPIO_H_

#include <cppunit/extensions/HelperMacros.h>
#include <dashee/GPIO.h>

/*
 * Set the namespace
 */
namespace dashee
{
    namespace test
    {
        class GPIO;
    }
}   

/**
 * GPIO test class for
 * unit testing known components
 */
class dashee::test::GPIO : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(dashee::test::GPIO);
    
    //CPPUNIT_TEST(testExport);

    // Exceptions
    //CPPUNIT_TEST_EXCEPTION(testInvalidFile, Exception_);
    
    CPPUNIT_TEST_SUITE_END();

private:
    dashee::GPIO * gpio;

protected:
    void testExport();

public:
    void setUp();
    void tearDown();
};

#endif
