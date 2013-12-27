/**
 * @file tests/Coordinate.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_TEST_COORDINATE_H_
#define DASHEE_TEST_COORDINATE_H_

#include <cppunit/extensions/HelperMacros.h>
#include <dashee/Coordinate.h>

/*
 * Set the namespace
 */
namespace dashee
{
    namespace test
    {
        class Coordinate;
    }
}   

/**
 * Buffer test class for
 * unit testing known components
 */
class dashee::test::Coordinate : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(dashee::test::Coordinate);
    
    CPPUNIT_TEST(testEmptyConstructions);
    CPPUNIT_TEST(testValueConstructions);

    CPPUNIT_TEST(testSetAndGetX);
    CPPUNIT_TEST(testSetAndGetY);
    CPPUNIT_TEST(testSetAndGetZ);
    
    CPPUNIT_TEST(testOperatorEquality);
    CPPUNIT_TEST(testOperatorPlusMinus);
    
    CPPUNIT_TEST_SUITE_END();

private:
    dashee::Coordinate<float> * coordinate;

protected:
    void testEmptyConstructions();
    void testValueConstructions();

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
