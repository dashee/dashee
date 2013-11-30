/**
 * @file tests/Threads.h
 * @author Shahmir Javaid
 *
 * @section LICENSE
 *
 * This file is licensed under the terms and condition
 * mentioned at http://dashee.co.uk/license. In general
 * you are free to copy, distribute, display, and perform the work, 
 * you are also free to make derivative works, under the following conditions:
 *  - Attribution    — You must give dashee's author credit.
 *  - Non-Commercial - You may not use this dashee for commercial 
 *                     purposes without permission.
 *  - Share Alike    — If you alter, transform, or build upon this work, 
 *                     you may distribute the resulting work only under a 
 *                     licence identical to this one.
 *
 * The terms and conditions are updated at http://dashee.co.uk/license. View the
 * project site for more details
 */

#ifndef DASHEE_TEST_THREADS_H_
#define DASHEE_TEST_THREADS_H_

#include <cppunit/extensions/HelperMacros.h>
#include <dashee/Threads/Thread.h>
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

	// Some function usefull for testing
	void * donothing(void *);
	void * waitTillExit(void *);
	void * doN(void * N);
	void * callSelf(void *);
	void * callExit(void *);
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

    void testCallingOneStartOnly();
    void testCallingJoinOnAStopedThread();

public:
    void setUp();
    void tearDown();
};

#endif
