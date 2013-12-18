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
    CPPUNIT_ASSERT(c1.getX() == 10);
    CPPUNIT_ASSERT(c1.getY() == 5);
    CPPUNIT_ASSERT(c1.getZ() == 20);
    
    // Negative values
    dashee::Coordinate<int> c2(-10, -5, -20);
    CPPUNIT_ASSERT(c2.getX() == -10);
    CPPUNIT_ASSERT(c2.getY() == -5);
    CPPUNIT_ASSERT(c2.getZ() == -20);
    
    // Mixed values
    dashee::Coordinate<int> c3(-10, 5, -20);
    CPPUNIT_ASSERT(c3.getX() == -10);
    CPPUNIT_ASSERT(c3.getY() == 5);
    CPPUNIT_ASSERT(c3.getZ() == -20);
}

/**
 * Test setting and getting X
 */
void dashee::test::Coordinate::testSetAndGetX()
{
    CPPUNIT_ASSERT(this->coordinate->getX() == 0.0f);
    this->coordinate->setX(1.9f);
    CPPUNIT_ASSERT(this->coordinate->getX() == 1.9f);
    this->coordinate->setX(-21.9f);
    CPPUNIT_ASSERT(this->coordinate->getX() == -21.9f);
}

/**
 * Test setting and getting Y
 */
void dashee::test::Coordinate::testSetAndGetY()
{
    CPPUNIT_ASSERT(this->coordinate->getY() == 0.0f);
    this->coordinate->setY(1.9f);
    CPPUNIT_ASSERT(this->coordinate->getY() == 1.9f);
    this->coordinate->setY(-21.9f);
    CPPUNIT_ASSERT(this->coordinate->getY() == -21.9f);
}

/**
 * Test setting and getting Y
 */
void dashee::test::Coordinate::testSetAndGetZ()
{
    CPPUNIT_ASSERT(this->coordinate->getZ() == 0.0f);
    this->coordinate->setZ(1.9f);
    CPPUNIT_ASSERT(this->coordinate->getZ() == 1.9f);
    this->coordinate->setZ(-21.9f);
    CPPUNIT_ASSERT(this->coordinate->getZ() == -21.9f);
}

/**
 * Tear down our objects
 */
void dashee::test::Coordinate::tearDown()
{
    delete this->coordinate;
}
