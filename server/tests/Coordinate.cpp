#include "Coordinate.h"

using namespace dashee::test;

/**
 * Set up our coordinate
 */
void Coordinate::setUp()
{
   this->coordinate = new dashee::Coordinate<float>();
}

/**
 * Test construction values as set by default
 */
void Coordinate::testEmptyConstructions()
{
    CPPUNIT_ASSERT(this->coordinate->getX() == 0.0f);
    CPPUNIT_ASSERT(this->coordinate->getY() == 0.0f);
    CPPUNIT_ASSERT(this->coordinate->getZ() == 0.0f);
}

/**
 * Test the copy constructor
 */
void Coordinate::testCopyConstructor()
{
    dashee::Coordinate<float> p1 = *this->coordinate;
    CPPUNIT_ASSERT(p1.getX() == 0.0f);
    CPPUNIT_ASSERT(p1.getY() == 0.0f);
    CPPUNIT_ASSERT(p1.getZ() == 0.0f);
}

/**
 * Test the assignment operator
 */
void Coordinate::testAssingmentOperator()
{
    dashee::Coordinate<float> p1;

    {
	dashee::Coordinate<float> p2(0.1f, 0.2f, 0.3f);

	// Assign
	p1 = p2;
    }

    CPPUNIT_ASSERT(p1.getX() == 0.1f);
    CPPUNIT_ASSERT(p1.getY() == 0.2f);
    CPPUNIT_ASSERT(p1.getZ() == 0.3f);
}

/**
 * Test construction of the object with values
 */
void Coordinate::testValueConstructions()
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
void Coordinate::testSetAndGetX()
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
void Coordinate::testSetAndGetY()
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
void Coordinate::testSetAndGetZ()
{
    CPPUNIT_ASSERT(this->coordinate->getZ() == 0.0f);
    this->coordinate->setZ(1.9f);
    CPPUNIT_ASSERT(this->coordinate->getZ() == 1.9f);
    this->coordinate->setZ(-21.9f);
    CPPUNIT_ASSERT(this->coordinate->getZ() == -21.9f);
}

/**
 * Test the equality operator
 */
void Coordinate::testOperatorEquality()
{
    // Check equality with two new objects
    CPPUNIT_ASSERT(dashee::Coordinate<int>() == dashee::Coordinate<int>());

    // Check equality with no value contractor and normal constructor
    CPPUNIT_ASSERT(
	    dashee::Coordinate<int>() == dashee::Coordinate<int>(0, 0, 0)
	);

    // Create c1, and c2 and test their equality
    dashee::Coordinate<float> c1(0.0f, 1.0f, 2.0f);
    dashee::Coordinate<float> c2(0.0f, 1.0f, 2.0f);
    CPPUNIT_ASSERT(c1 == c2);

    // Change this coordinate and test equality
    c1.setX(0.0f);
    c1.setY(1.0f);
    c1.setZ(2.0f);
    CPPUNIT_ASSERT(c1 != dashee::Coordinate<float>());
}

/**
 * Test the plus and minus operator
 */
void Coordinate::testOperatorPlusMinus()
{
    // Create c1, and c2 and test the value with + and -
    dashee::Coordinate<float> c1(0.0f, 1.0f, 2.0f);
    dashee::Coordinate<float> c2(0.0f, 1.0f, 2.0f);
    CPPUNIT_ASSERT((c1 + c2) == dashee::Coordinate<float>(0.0f, 2.0f, 4.0f));
    CPPUNIT_ASSERT((c1 - c2) == dashee::Coordinate<float>(0.0f, 0.0f, 0.0f));
}

/**
 * Tear down our objects
 */
void Coordinate::tearDown()
{
    delete this->coordinate;
}
