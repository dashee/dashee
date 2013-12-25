/**
 * @file tests/Point.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_TEST_POINT_H_
#define DASHEE_TEST_POINT_H_

#include <cppunit/extensions/HelperMacros.h>
#include <dashee/Point.h>
#include <dashee/Log.h>

/*
 * Set the namespace
 */
namespace dashee
{
    namespace test
    {
        class Point;
    }
}   

/**
 * Buffer test class for
 * unit testing known components
 */
class dashee::test::Point : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(dashee::test::Point);
    
    CPPUNIT_TEST(testEmptyConstructions);
    CPPUNIT_TEST(testValueConstructions);
    CPPUNIT_TEST(testCopyConstructor);
    CPPUNIT_TEST(testAssingmentOperator);

    CPPUNIT_TEST(testSetAndGetX);
    CPPUNIT_TEST(testSetAndGetY);
    CPPUNIT_TEST(testSetAndGetZ);
    
    CPPUNIT_TEST(testOperatorEquality);
    CPPUNIT_TEST(testOperatorPlusMinus);
    
    CPPUNIT_TEST_SUITE_END();

private:
    dashee::Point<float> * point;

protected:
    void testEmptyConstructions();
    void testValueConstructions();
    void testCopyConstructor();
    void testAssingmentOperator();

    void testSetAndGetX();
    void testSetAndGetY();
    void testSetAndGetZ();

    void testOperatorEquality();
    void testOperatorPlusMinus();

public:
    void setUp();
    void tearDown();
};

#endif
