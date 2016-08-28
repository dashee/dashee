#include "Buffer.h"

/**
 * Start up
 */ 
void dashee::test::Buffer::setUp()
{
    this->buffer = new dashee::Buffer<int>();
}

/**
 * Simple test which checks wheather or not the file
 * is 
 */
void dashee::test::Buffer::testWriteAndRead()
{
    CPPUNIT_ASSERT(this->buffer->size() == 0);
    this->buffer->push(10);
    CPPUNIT_ASSERT(this->buffer->size() == 1);
    CPPUNIT_ASSERT(this->buffer->next() == 10);
    CPPUNIT_ASSERT(this->buffer->size() == 0);

    // Add a 100 items and test thier size
    for (size_t x = 0; x < this->buffer->size(); x++)
    {
	this->buffer->push(x+100u);
	CPPUNIT_ASSERT(this->buffer->size() == x);
    }
    
    // Call next a 100 times and test the size value and also
    // the next value
    for (size_t x = 0; x < this->buffer->size(); x++)
    {
	CPPUNIT_ASSERT(this->buffer->next() == static_cast<int>(x)+100);
	CPPUNIT_ASSERT(this->buffer->size() == static_cast<size_t>(100-x));
    }
}

/**
 * When requesting the next buffer byte and there are none left
 * an ExceptionOutOfBounds should be thrown
 */
void dashee::test::Buffer::testOutOfBounds()
{
    this->buffer->push(10);
    this->buffer->next();
    this->buffer->next();
}

/**
 * Clean up
 */
void dashee::test::Buffer::tearDown()
{
    delete this->buffer;
}
