#include "Thread.h"

/**
 * Dummy function which does nothing and returns
 *
 * @param nothing not used
 */ 
void * dashee::test::donothing(void * nothing)
{
    CPPUNIT_ASSERT(true);
    return;
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
	pthread_mutex_lock(&mutexRUN);
	if (RUN == false) break;
	pthread_mutex_unlock(&mutexRUN);

	sleep(100);
    }

    return;
}

/**
 * Do an operation N times and sleep through every iteration
 *
 * @param N Integer pointer to the number of times an operation must be done
 */
void * dashee::test::doN(void * N)
{
    for (int x = 0; x < *(reinterpret_cast<int *>N); x++)
    {
	pthread_mutex_lock(&mutexRUN);
	if (RUN == false) break;
	pthread_mutex_unlock(&mutexRUN);

	sleep(100);
    }

    return;
    
}

/**
 * This will call the self function and ensure that the value returned is not
 * null
 *
 * @param nothing not used
 */ 
void * dashee::test::callSelf(void * nothing)
{
    CPPUNIT_ASSERT(Thread::self() != NULL);
    Thread::exit();
    return;
}

/**
 * Call exit within the thread to ensure things perform well
 * 
 * @param nothing not used
 */
void * dashee::test::callExit(void * nothing)
{
    Thread::exit();
    CPPUNIT_ASSERT(true);
    return;
}   

/**
 * Do nothing
 */
void dashee::test::Thread::setUp()
{
}

/**
 * Test a simple 
 */
void dashee::test::Thread::testWorking()
{
    this->thread = new Thread(dashee::test::donothing);
    this->thread.start((void *)NULL);
    this->thread.join();

    delete this->thread;
}

/**
 * Test pool size.
 *
 * Create threads, start them and join them and test the pool size value on 
 * every iteration
 */
void dashee::test::Thread::testPoolSize()
{
    // No initilized threads hold the size of 0
    CPPUNIT_ASSERT(Thread::size() == 0);
 
    this->thread = new Thread(dashee::test::donothing);
    
    // A thread must must must be started before the size value is set to +1
    CPPUNIT_ASSERT(Thread::size() == 0);


    this->thread->start((void *)NULL);
    
    // Calling a thread size is safe, after thread start because the adding of 1
    // to the size is done in the main thread.
    CPPUNIT_ASSERT(Thread::size() == 1);

    // Join to ensure the end of thread, and the value of size must still be the
    // same
    this->thread->join();
    CPPUNIT_ASSERT(Thread::size() == 1);

    // Adding another thread and starting it to test the size growth
    Thread * temp = new Thread(donothing);
    temp->start((void *)NULL);
    CPPUNIT_ASSERT(Thread::size() == 2);

    // Delete a thread is the only time the pool of threads must be deleted
    temp->join();
    delete temp;
    CPPUNIT_ASSERT(Thread::size() == 1);

    delete this->thread;
    CPPUNIT_ASSERT(Thread::size() == 0);
}

/**
 * You can't start a thread twice asynchronisly but you can do it synchronisly.
 */
void dashee::test::Thread::testMultiStart()
{
    this->thread = new Thread(donothing);
    this->thread->start((void *)NULL);
    this->thread->join();
    CPPUNIT_ASSERT(true);

    this->thread->start((void *)NULL);
    this->thread->join();
    CPPUNIT_ASSERT(true);
    
    this->thread->start((void *)NULL);
    this->thread->join();
    CPPUNIT_ASSERT(true);
}   

/**
 * Simple thread just runs callSelf, which is asserted
 */
void dashee::test::Thread::testSelfCall()
{
    this->thread = new Thread(callSelf);
    this->thread->start((void *)NULL);
    this->thread->join();
}

/**
 * Simple thread just runs callSelf, which is asserted
 */
void dashee::test::Thread::testExits()
{
    this->thread = new Thread(callExit);
    this->thread->start((void *)NULL);
    this->thread->join();
}

/**
 * This function should throw an exception because a thread must only be 
 * started once
 */
void dashee::test::Thread::testCallingOneStartOnly()
{
    this->thread = new Thread(donothing);
    this->thread->start((void *)NULL);
    this->thread->start((void *)NULL);
    this->thread->join();
}

/**
 * Calling exit on non threads is not allowed
 */
void dashee::test::Thread::testCallingExitOnNotathread()
{
    Thread::exit();
}

/**
 * Join must only be initiated on started threads
 */
void dashee::test::Thread::testCallingJoinOnAStopedThread()
{
    this->thread = new Thread(donothing);
    this->thread->join();
}

/**
 * Kill any thread still running, especially detached ones, by
 * changing the flag of RUN, test assumes RUN to be global, and one set
 * may only run a set of threads and must also close any threads. If not
 * teardown should manage to change RUN where all threads should respond
 */ 
void dashee::test::Thread::tearDown()
{
    pthread_mutex_lock(&mutexRUN);
    RUN = false;
    pthread_mutex_unlock(&mutexRUN);
}
