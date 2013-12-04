/**
 * @file tests/Threads.h
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. 
 */

#ifndef DASHEE_TEST_THREADS_H_
#define DASHEE_TEST_THREADS_H_

#include <cppunit/extensions/HelperMacros.h>
#include <dashee/Threads/Thread.h>
#include <dashee/Threads/Lock/ReadWrite.h>
#include <dashee/Threads/Lock/Mutex.h>
#include "dashee.h"

/*
 * Set the namespace
 */
namespace dashee
{
    namespace test
    {
        class Threads;

	// Variables to control global thread run state, usefull 
	// to flag threads to stop
	extern volatile bool RUN;
	extern dashee::Threads::LockMutex mutexRUN;
	
        // Variable to change in accordance to threads
        // to test thier value
        extern volatile int sharedVariable;
	
        // Create a set of locks
        extern dashee::Threads::LockMutex lockMutex;
        extern dashee::Threads::LockReadWrite lockReadWrite;

	// Some function usefull for testing
	void * donothing(void *);
	void * waitTillExit(void *);
	void * doN(void * N);
	void * callSelf(void *);
	void * callExit(void *);
	void * addNTimes(void * l);
	void * exitValue(void * v);

        // Function which takes in a mutex, and tries to
        // double lock it
        void * doubleLock(void * l);
    }
}

/**
 * GPIO test class for
 * unit testing known components
 */
class dashee::test::Threads : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(dashee::test::Threads);
    
    // Test Joining as well as detached thread is sort of hard to test, 
    // thoughts an ideas please do all
    CPPUNIT_TEST(testWorking);
    
    // Test to see multiple starts of the same thread work
    CPPUNIT_TEST(testMultiStarts);

    // Some generic functions to tests, see definition description
    CPPUNIT_TEST(testSelfCall);
    CPPUNIT_TEST(testExits);
    
    CPPUNIT_TEST(testLock);
    CPPUNIT_TEST(testDoubleLock);

    // Calling start twice should
    CPPUNIT_TEST_EXCEPTION(
	    testCallingOneStartOnly, 
	    dashee::Threads::ExceptionThreadNorestart
	);
    
    // Joining a thread that is not started, dont be a fool
    CPPUNIT_TEST_EXCEPTION(
	    testCallingJoinOnAStopedThread, 
	    dashee::Threads::ExceptionThread
	);
    
    CPPUNIT_TEST_SUITE_END();

private:
    dashee::Threads::Thread * thread;

protected:
    void testWorking();
    void testMultiStarts();
    void testSelfCall();
    void testExits();
    
    void testLock();
    void testDoubleLock();

    void testCallingOneStartOnly();
    void testCallingJoinOnAStopedThread();

public:
    void setUp();
    void tearDown();
};

#endif
