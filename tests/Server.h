/**
 * @file tests/Server.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_TEST_SERVER_H_
#define DASHEE_TEST_SERVER_H_

#include <cppunit/extensions/HelperMacros.h>
#include <dashee/Server.h>

/*
 * Set the namespace
 */
namespace dashee
{
    namespace test
    {
        class Server;
    }
}   

/**
 * Server test class for
 * unit testing known components
 */
class dashee::test::Server : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(dashee::test::Server);
    
    //CPPUNIT_TEST(testSetAndGet);

    // Exceptions
    //CPPUNIT_TEST_EXCEPTION(testInvalidKeyException, ExceptionConfig);
    
    CPPUNIT_TEST_SUITE_END();

private:
    dashee::Server * server;

protected:
    //virtual void testCleanUp();

public:
    virtual void setUp();
    virtual void tearDown();
};

#endif
