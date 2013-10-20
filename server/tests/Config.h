/**
 * @file tests/Config.h
 * @author Shahmir Javaid
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. In general
 * you are free to copy, distribute, display, and perform the work, 
 * you are also free to make derivative works, under the following conditions:
 *  - Attribution    — You must give dashee's author credit.
 *  - Non-Commercial - You may not use this dashee for commercial 
 *                     purposes without permission.
 *  - Share Alike    — If you alter, transform, or build upon this work, 
 *                     you may distribute the resulting work only under a licence 
 *                     identical to this one.
 *
 * The terms and conditions are updated at http://dashee.co.uk/license. View the
 * project site for more details
 */

#ifndef DASHEE_TEST_CONFIG_H_
#define DASHEE_TEST_CONFIG_H_

#include <cppunit/extensions/HelperMacros.h>
#include <dashee/Config.h>

/*
 * Set the namespace
 */
namespace dashee
{
    namespace test
    {
        class Config;
    }
}   

/**
 * GPIO test class for
 * unit testing known components
 */
class dashee::test::Config : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(dashee::test::Config);
    
    CPPUNIT_TEST(testSetAndGet);
    CPPUNIT_TEST(testSetAndGetInt);
    CPPUNIT_TEST(testSetAndGetUnsignedInt);
    CPPUNIT_TEST(testSetAndGetFloat);
    CPPUNIT_TEST(testReadConfig);
    CPPUNIT_TEST(testReadConfigWithErrors);
    CPPUNIT_TEST(testSize);
    CPPUNIT_TEST(testCleanUp);

    // Exceptions
    CPPUNIT_TEST_EXCEPTION(testInvalidKeyException, ExceptionConfig);
    
    CPPUNIT_TEST_SUITE_END();

private:
    dashee::Config * config;

protected:
    void testDefault();
    void testSetAndGet();
    void testSetAndGetInt();
    void testSetAndGetUnsignedInt();
    void testSetAndGetFloat();
    void testReadConfig();
    void testReadConfigWithErrors();
    void testSize();
    void testCleanUp();

    void testInvalidKeyException();

public:
    void setUp();
    void tearDown();
};

#endif
