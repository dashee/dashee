/**
 * @file tests/Buffer.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_TEST_BUFFER_H_
#define DASHEE_TEST_BUFFER_H_

#include <cppunit/extensions/HelperMacros.h>
#include <dashee/Buffer.h>

/*
 * Set the namespace
 */
namespace dashee
{
    namespace test
    {
        class Buffer;
    }
}   

/**
 * Buffer test class for
 * unit testing known components
 */
class dashee::test::Buffer : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(dashee::test::Buffer);
    
    CPPUNIT_TEST(testWriteAndRead);

    // Exceptions
    CPPUNIT_TEST_EXCEPTION(testOutOfBounds, dashee::ExceptionOutOfBounds);
    
    CPPUNIT_TEST_SUITE_END();

private:
    dashee::Buffer<int> * buffer;

protected:
    void testWriteAndRead();
    void testOutOfBounds();

public:
    void setUp();
    void tearDown();
};

#endif

