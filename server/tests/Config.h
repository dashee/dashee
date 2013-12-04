/**
 * @file tests/Config.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
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
    CPPUNIT_TEST(testIsKeySet);
    CPPUNIT_TEST(testReadConfig);
    CPPUNIT_TEST(testReadConfigWithErrors);
    CPPUNIT_TEST(testSize);
    CPPUNIT_TEST(testCleanUp);

    // Exceptions
    CPPUNIT_TEST_EXCEPTION(testInvalidKeyException, ExceptionConfig);
    CPPUNIT_TEST_EXCEPTION(testInvalidKeyExceptionPreDash, ExceptionConfig);
    CPPUNIT_TEST_EXCEPTION(testInvalidKeyExceptionPostDash, ExceptionConfig);
    CPPUNIT_TEST_EXCEPTION(testInvalidKeyExceptionPreHyphen, ExceptionConfig);
    CPPUNIT_TEST_EXCEPTION(testInvalidKeyExceptionPostHyphen, ExceptionConfig);
    CPPUNIT_TEST_EXCEPTION(testInvalidKeyExceptionPreNumber, ExceptionConfig);
    
    CPPUNIT_TEST_SUITE_END();

private:
    dashee::Config * config;

protected:
    void testDefault();
    void testSetAndGet();
    void testSetAndGetInt();
    void testSetAndGetUnsignedInt();
    void testSetAndGetFloat();
    void testIsKeySet();
    void testReadConfig();
    void testReadConfigWithErrors();
    void testSize();
    void testCleanUp();

    void testInvalidKeyException();
    void testInvalidKeyExceptionPreDash();
    void testInvalidKeyExceptionPostDash();
    void testInvalidKeyExceptionPreHyphen();
    void testInvalidKeyExceptionPostHyphen();
    void testInvalidKeyExceptionPreNumber();

public:
    /**
     * Where the temp configuration files are stored
     * for testing
     */ 
    static char * directoryPath;

    void setUp();
    void tearDown();
};

#endif
