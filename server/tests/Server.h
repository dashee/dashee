/**
 * @file tests/Server.h
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
