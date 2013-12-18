#include "Coordinate.h"

/**
 * Set up our coordinate
 */
void dashee::test::Coordinate::setUp()
{
   this->coordinate = new dashee::Coordinate<float>();     
}

/**
 * Test construction values as set by default
 */
void dashee::test::Coordinate::testEmptyConstructions()
{
    CPPUNIT_ASSERT(this->coordinate->getX() == 0.0f);
    CPPUNIT_ASSERT(this->coordinate->getY() == 0.0f);
    CPPUNIT_ASSERT(this->coordinate->getZ() == 0.0f);
}

/**
 * Test construction of the object with values
 */
void dashee::test::Coordinate::testValueConstructions()
{
    // Positive Values
    dashee::Coordinate<int> c1(10,5,20);
    CPPUNIT_ASSERT(this->coordinate->getX() == 10);
    CPPUNIT_ASSERT(this->coordinate->getY() == 5);
    CPPUNIT_ASSERT(this->coordinate->getZ() == 1);
    
    // Negative values
    dashee::Coordinate<int> c2(-10, -5, -20);
    CPPUNIT_ASSERT(this->coordinate->getX() == -10);
    CPPUNIT_ASSERT(this->coordinate->getY() == -5);
    CPPUNIT_ASSERT(this->coordinate->getZ() == -20);
    
    // Mixed values
    dashee::Coordinate<int> c3(-10, 5, -20);
    CPPUNIT_ASSERT(this->coordinate->getX() == -10);
    CPPUNIT_ASSERT(this->coordinate->getY() == 5);
    CPPUNIT_ASSERT(this->coordinate->getZ() == -20);
}

/**
 * Test setting and getting X
 */
void dashee::test::Coordinate::testSetAndGetX()
{
    CPPUNIT_ASSERT(false);
}

/**
 * Test setting and getting Y
 */
void dashee::test::Coordinate::testSetAndGetY()
{
    CPPUNIT_ASSERT(false);
}

/**
 * Test setting and getting Y
 */
void dashee::test::Coordinate::testSetAndGetZ()
{
    CPPUNIT_ASSERT(false);
}

/**
 * Tear down our objects
 */
void dashee::test::Coordinate::tearDown()
{
    delete this->coordinate;
}
