#include "Threads.h"

volatile bool dashee::test::RUN = false;
dashee::Threads::LockMutex dashee::test::mutexRUN 
    = dashee::Threads::LockMutex();

/**
 * Dummy function which does nothing and returns
 *
 * @param nothing not used
 */ 
void * dashee::test::donothing(void * nothing)
{
    CPPUNIT_ASSERT(true);
    return NULL;
}

/**
 * This is a function which infinatly loops till the RUN flag is changed
 *
 * @param nothing not used
 */
void * dashee::test::waitTillExit(void * nothing)
{
    while (true)
    {
	mutexRUN.lock();
	if (RUN == false) 
	    break;
	mutexRUN.unlock();

	sleep(100);
    }

    return NULL;
}

/**
 * Do an operation N times and sleep through every iteration
 *
 * @param N Integer pointer to the number of times an operation must be done
 */
void * dashee::test::doN(void * N)
{
    for (int x = 0; x < *(reinterpret_cast<int *>(N)); x++)
    {
	mutexRUN.lock();
	if (RUN == false) break;
	mutexRUN.lock();

	sleep(100);
    }

    return NULL;
    
}

/**
 * This will call the self function and ensure that the value returned is not
 * null
 *
 * @param nothing not used
 */ 
void * dashee::test::callSelf(void * nothing)
{
    CPPUNIT_ASSERT(dashee::Threads::Thread::self() > 0);
    dashee::Threads::Thread::exit();
    return NULL;
}

/**
 * Call exit within the thread to ensure things perform well
 * 
 * @param nothing not used
 */
void * dashee::test::callExit(void * nothing)
{
    dashee::Threads::Thread::exit();
    CPPUNIT_ASSERT(true);
    return NULL;
}   

/**
 * Do nothing
 */
void dashee::test::Threads::setUp()
{
}

/**
 * Test a simple 
 */
void dashee::test::Threads::testWorking()
{
    this->thread = new dashee::Threads::Thread(dashee::test::donothing);
    this->thread->start((void *)NULL);
    this->thread->join();

    delete this->thread;
}

/**
 * You can't start a thread twice asynchronisly but you can do it synchronisly.
 */
void dashee::test::Threads::testMultiStarts()
{
    this->thread = new dashee::Threads::Thread(donothing);
    this->thread->start((void *)NULL);
    this->thread->join();
    CPPUNIT_ASSERT(true);

    this->thread->start((void *)NULL);
    this->thread->join();
    CPPUNIT_ASSERT(true);
    
    this->thread->start((void *)NULL);
    this->thread->join();
    CPPUNIT_ASSERT(true);

    delete this->thread;
}   

/**
 * Simple thread just runs callSelf, which is asserted
 */
void dashee::test::Threads::testSelfCall()
{
    this->thread = new dashee::Threads::Thread(callSelf);
    this->thread->start((void *)NULL);
    this->thread->join();
}

/**
 * Simple thread just runs callSelf, which is asserted
 */
void dashee::test::Threads::testExits()
{
    this->thread = new dashee::Threads::Thread(callExit);
    this->thread->start((void *)NULL);
    this->thread->join();
}

/**
 * This function should throw an exception because a thread must only be 
 * started once
 */
void dashee::test::Threads::testCallingOneStartOnly()
{
    this->thread = new dashee::Threads::Thread(donothing);
    this->thread->start((void *)NULL);
    this->thread->start((void *)NULL);
    this->thread->join();
}

/**
 * Join must only be initiated on started threads
 */
void dashee::test::Threads::testCallingJoinOnAStopedThread()
{
    this->thread = new dashee::Threads::Thread(donothing);
    this->thread->join();
}

/**
 * Kill any thread still running, especially detached ones, by
 * changing the flag of RUN, test assumes RUN to be global, and one set
 * may only run a set of threads and must also close any threads. If not
 * teardown should manage to change RUN where all threads should respond
 */ 
void dashee::test::Threads::tearDown()
{
    mutexRUN.lock();
    RUN = false;
    mutexRUN.unlock();
}
