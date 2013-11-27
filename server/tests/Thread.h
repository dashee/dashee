/**
 * @file tests/Thread.h
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

#ifndef DASHEE_TEST_THREAD_H_
#define DASHEE_TEST_THREAD_H_

#include <cppunit/extensions/HelperMacros.h>
#include <dashee/Thread.h>
#include "dashee.h"

/*
 * Set the namespace
 */
namespace dashee
{
    namespace test
    {
        class Thread;

	// Variables to control global thread run state, usefull 
	// to flag threads to stop
	volatile bool RUN = false;
	pthread_mutex_t mutexRUN = PTHREAD_MUTEX_INITIALIZER;

	// Some function usefull for testing
	void * donothing(void *);
	void * waitTillExit(void *);
	void * doN(void * N);
	void * callSelf();
	void * callExit(void *);
    }
}   

/**
 * GPIO test class for
 * unit testing known components
 */
class dashee::test::Thread : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(dashee::test::Thread);
    
    // Test Joining as well as detached thread is sort of hard to test, 
    // thoughts an ideas please do all
    CPPUNIT_TEST(testThread);
    
    CPPUNIT_TEST(testMultiStarts);

    // Some generic functions to tests, see definition description
    CPPUNIT_TEST(testPoolSize);
    CPPUNIT_TEST(testSelfCall);
    CPPUNIT_TEST(testExits);

    // Calling start twice should
    CPPUNIT_TEST_EXCEPTION(
	    testCallingOneStartOnly, 
	    ExceptionThreadNorestart
	);

    // Calling exit on main is bad
    CPPUNIT_TEST_EXCEPTION(
	    testCallingExitOnNotathread, 
	    ExceptionThreadNotathread
	);
    
    // Joining a thread that is not started, dont be a fool
    CPPUNIT_TEST_EXCEPTION(
	    testCallingJoinOnAStopedThread, 
	    ExceptionThread
	);
    
    CPPUNIT_TEST_SUITE_END();

private:
    dashee::Thread * thread;

protected:
    void testWorking();
    void testPoolSize();
    void testSelfCall();
    void testExits();

    void testCallingOneStartOnly();
    void testCallingExitOnNotathread();
    void testCallingJoinOnAStopedThread();

public:
    void setUp();
    void tearDown();
};

#endif
