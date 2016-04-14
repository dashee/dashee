#include "Point.h"

using namespace dashee::test;

/**
 * Set up our point
 */
void Point::setUp()
{
   this->point = new dashee::Point<float>();
}

/**
 * Test construction values as set by default
 */
void Point::testEmptyConstructor()
{
    CPPUNIT_ASSERT(this->point->getX() == 0.0f);
    CPPUNIT_ASSERT(this->point->getY() == 0.0f);
    CPPUNIT_ASSERT(this->point->getZ() == 0.0f);
}

/**
 * Test the construction using one value
 */
void Point::testOneValueConstructor()
{
    dashee::Point<int> p1(10);
    CPPUNIT_ASSERT(p1.getX() == 10);
    CPPUNIT_ASSERT(p1.getY() == 10);
    CPPUNIT_ASSERT(p1.getZ() == 10);

    dashee::Point<int> p2 = 5;
    CPPUNIT_ASSERT(p2.getX() == 5);
    CPPUNIT_ASSERT(p2.getY() == 5);
    CPPUNIT_ASSERT(p2.getZ() == 5);
}

/**
 * Test construction of the object with values
 */
void Point::testValueConstructor()
{
    // Positive Values
    dashee::Point<int> p1(10,5,20);
    CPPUNIT_ASSERT(p1.getX() == 10);
    CPPUNIT_ASSERT(p1.getY() == 5);
    CPPUNIT_ASSERT(p1.getZ() == 20);
    
    // Negative values
    dashee::Point<int> p2(-10, -5, -20);
    CPPUNIT_ASSERT(p2.getX() == -10);
    CPPUNIT_ASSERT(p2.getY() == -5);
    CPPUNIT_ASSERT(p2.getZ() == -20);
    
    // Mixed values
    dashee::Point<int> p3(-10, 5, -20);
    CPPUNIT_ASSERT(p3.getX() == -10);
    CPPUNIT_ASSERT(p3.getY() == 5);
    CPPUNIT_ASSERT(p3.getZ() == -20);
}

/**
 * Test the copy constructor
 */ 
void Point::testCopyConstructor()
{
    dashee::Point<int> p1(10);
    dashee::Point<int> p2 = p1;
    CPPUNIT_ASSERT(p2.getX() == 10);
    CPPUNIT_ASSERT(p2.getY() == 10);
    CPPUNIT_ASSERT(p2.getZ() == 10);
}

/**
 * Test the assignment operator
 */
void Point::testAssingmentOperator()
{
    dashee::Point<float> p1;

    {
	dashee::Point<float> p2(0.1f, 0.2f, 0.3f);

	// Assign
	p1 = p2;
    }

    CPPUNIT_ASSERT(p1.getX() == 0.1f);
    CPPUNIT_ASSERT(p1.getY() == 0.2f);
    CPPUNIT_ASSERT(p1.getZ() == 0.3f);
}

/**
 * Test setting and getting X
 */
void Point::testSetAndGetX()
{
    CPPUNIT_ASSERT(this->point->getX() == 0.0f);
    this->point->setX(1.9f);
    CPPUNIT_ASSERT(this->point->getX() == 1.9f);
    this->point->setX(-21.9f);
    CPPUNIT_ASSERT(this->point->getX() == -21.9f);
}

/**
 * Test setting and getting Y
 */
void Point::testSetAndGetY()
{
    CPPUNIT_ASSERT(this->point->getY() == 0.0f);
    this->point->setY(1.9f);
    CPPUNIT_ASSERT(this->point->getY() == 1.9f);
    this->point->setY(-21.9f);
    CPPUNIT_ASSERT(this->point->getY() == -21.9f);
}

/**
 * Test setting and getting Y
 */
void Point::testSetAndGetZ()
{
    CPPUNIT_ASSERT(this->point->getZ() == 0.0f);
    this->point->setZ(1.9f);
    CPPUNIT_ASSERT(this->point->getZ() == 1.9f);
    this->point->setZ(-21.9f);
    CPPUNIT_ASSERT(this->point->getZ() == -21.9f);
}

/**
 * Test the equality operator
 */
void Point::testOperatorEquality()
{
    // Check equality with two new objects
    CPPUNIT_ASSERT(dashee::Point<int>() == dashee::Point<int>());

    // Check equality with no value contractor and normal constructor
    CPPUNIT_ASSERT(
	    dashee::Point<int>() == dashee::Point<int>(0, 0, 0)
	);

    // Create p1, and p2 and test their equality
    dashee::Point<float> p1(0.0f, 1.0f, 2.0f);
    dashee::Point<float> p2(0.0f, 1.0f, 2.0f);
    CPPUNIT_ASSERT(p1 == p2);

    // Change this point and test equality
    p1.setX(0.0f);
    p1.setY(1.0f);
    p1.setZ(2.0f);
    CPPUNIT_ASSERT(p1 != dashee::Point<float>());
}

/**
 * Test the plus and minus operator
 */
void Point::testOperatorPlusMinus()
{
    // Create p1, and p2 and test the value with + and -
    dashee::Point<float> p1(0.0f, 1.0f, 2.0f);
    dashee::Point<float> p2(0.0f, 1.0f, 2.0f);
    dashee::Point<float> p3(0.1f, 0.1f, 0.1f);
    CPPUNIT_ASSERT((p1 + p2) == dashee::Point<float>(0.0f, 2.0f, 4.0f));
    CPPUNIT_ASSERT((p1 - p2) == dashee::Point<float>(0.0f, 0.0f, 0.0f));
    CPPUNIT_ASSERT((p1 + p2 + p3) == dashee::Point<float>(0.1f, 2.1f, 4.1f));
    CPPUNIT_ASSERT((p1 + p2 - p3) == dashee::Point<float>(-0.1f, 1.9f, 3.9f));
    CPPUNIT_ASSERT((p1 - p2 + p3) == p3);

}

/**
 * Test the plus and minus operator
 */
void Point::testOperatorMultiply()
{
    // Multiply p1 by 2.0 and 0.5
    dashee::Point<float> p1(0.0f, 1.0f, 2.0f);
    CPPUNIT_ASSERT((p1 * 0.5f) == dashee::Point<float>(0.0f, 0.5f, 1.0f));
    CPPUNIT_ASSERT((2.0f * p1) == dashee::Point<float>(0.0f, 2.0f, 4.0f));

    p1 *= 0.5f;
    CPPUNIT_ASSERT(p1 == dashee::Point<float>(0.0f, 0.5f, 1.0f));
}

/**
 * Tear down our objects
 */
void Point::tearDown()
{
    delete this->point;
}
