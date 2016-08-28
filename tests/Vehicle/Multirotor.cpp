#include "Vehicle/Multirotor.h"

using namespace dashee::test;

/**
 * Test reading the buffer value and setting the appropriate 
 * flight control value
 */
void VehicleMultirotor::testReadFromBuffer()
{
    dashee::Buffer<unsigned char> q;
    
    // Push one command and see the status
    q.push(0);
    q.push(0);
    q.push(0);
    q.push(0);
    q.push(0);
    this->vehicle->read(&q);
    CPPUNIT_ASSERT(this->vehicle->getPitch() == 0);
    CPPUNIT_ASSERT(this->vehicle->getRoll() == 0);
    CPPUNIT_ASSERT(this->vehicle->getYaw() == 0);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 0);
    CPPUNIT_ASSERT(q.empty() == true);

    // Push another command and see the changed
    q.push(0);
    q.push(10);
    q.push(11);
    q.push(12);
    q.push(13);
    this->vehicle->read(&q);
    CPPUNIT_ASSERT(this->vehicle->getPitch() == 10);
    CPPUNIT_ASSERT(this->vehicle->getRoll() == 11);
    CPPUNIT_ASSERT(this->vehicle->getYaw() == 12);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 13);
    CPPUNIT_ASSERT(q.empty() == true);

    // Push two commands and check that the values are set to the
    // last known value
    q.push(0);
    q.push(20);
    q.push(20);
    q.push(20);
    q.push(20);
    q.push(0);
    q.push(30);
    q.push(31);
    q.push(32);
    q.push(33);
    this->vehicle->read(&q);
    CPPUNIT_ASSERT(this->vehicle->getPitch() == 30);
    CPPUNIT_ASSERT(this->vehicle->getRoll() == 31);
    CPPUNIT_ASSERT(this->vehicle->getYaw() == 32);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 33);
    CPPUNIT_ASSERT(q.empty() == true);

    // Test invalid set of commands
    q.push(10);
    q.push(11);
    q.push(12);
    this->vehicle->read(&q);
    CPPUNIT_ASSERT(this->vehicle->getPitch() == 30);
    CPPUNIT_ASSERT(this->vehicle->getRoll() == 31);
    CPPUNIT_ASSERT(this->vehicle->getYaw() == 32);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 33);
    CPPUNIT_ASSERT(q.empty() == true);

    // Test invalid set of commands
    q.push(10);
    q.push(11);
    q.push(12);
    q.push(0);
    q.push(40);
    q.push(41);
    q.push(42);
    q.push(43);
    q.push(10);
    this->vehicle->read(&q);
    CPPUNIT_ASSERT(this->vehicle->getPitch() == 40);
    CPPUNIT_ASSERT(this->vehicle->getRoll() == 41);
    CPPUNIT_ASSERT(this->vehicle->getYaw() == 42);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() == 43);
    CPPUNIT_ASSERT(q.empty() == true);
    
    CPPUNIT_ASSERT(this->vehicle->getPitch() != 255);
    CPPUNIT_ASSERT(this->vehicle->getRoll() != 255);
    CPPUNIT_ASSERT(this->vehicle->getYaw() != 255);
    CPPUNIT_ASSERT(this->vehicle->getThrottle() != 255);
}

/**
 * The motor only has a max limit of channels, ensure that Quad or Hex vehicles
 * throw exceptions if the invalid set motor is set
 */ 
void VehicleMultirotor::testInvalidMotorChannel()
{
    throw dashee::Exception("This must be implemented by a child function");
}
