#include "Threads.h"

volatile bool dashee::test::RUN = false;
dashee::Threads::LockMutex dashee::test::mutexRUN 
    = dashee::Threads::LockMutex();

volatile int dashee::test::sharedVariable = 0;

// Initialize the different lock types
dashee::Threads::LockMutex dashee::test::lockMutex
    = dashee::Threads::LockMutex();
dashee::Threads::LockReadWrite dashee::test::lockReadWrite
    = dashee::Threads::LockReadWrite();

/**
 * Dummy function which does nothing and returns
 *
 * @param nothing not used
 * 
 * @returns Nothing
 */ 
void * dashee::test::donothing(void * nothing)
{
    UNUSED(nothing);
    CPPUNIT_ASSERT(true);
    return NULL;
}

/**
 * This is a function which infinitely loops till the RUN flag is changed
 *
 * @param nothing not used
 * 
 * @returns Nothing
 */
void * dashee::test::waitTillExit(void * nothing)
{
    UNUSED(nothing);
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
 * 
 * @returns Nothing
 */
void * dashee::test::doN(void * N)
{
    for (int x = 0; x < *(static_cast<int *>(N)); x++)
    {
	mutexRUN.lock();
	if (RUN == false) break;
	mutexRUN.lock();

	sleep(100);
    }

    return NULL;
}

/**
 * This will add 1 to the shared variables, Multiple threads can be
 * set lose to this to ensure that the value accumulates correctly
 *
 * @param l The dashee::Threads::Lock object
 *
 * @returns Nothing
 */
void * dashee::test::addNTimes(void * l)
{
    dashee::Threads::Lock * lock 
        = static_cast<dashee::Threads::Lock *>(l);

    // Do nothing for a while, so other threads can 
    // try to fight for locks
    for (int x = 0; x < 100; x++)
    {
        lock->lock(dashee::Threads::Lock::LOCKTYPE_WRITE);
        
        dashee::test::sharedVariable++;
        sleep(100);

        lock->unlock();
    }

    return NULL;
}

/**
 * This will call the self function and ensure that the value returned is not
 * null
 *
 * @param nothing not used
 * 
 * @returns Nothing
 */ 
void * dashee::test::callSelf(void * nothing)
{
    UNUSED(nothing);
    CPPUNIT_ASSERT(dashee::Threads::Thread::self() > 0);
    dashee::Threads::Thread::exit();
    return NULL;
}

/**
 * Call exit within the thread to ensure things perform well
 * 
 * @param nothing not used
 * 
 * @returns Nothing
 */
void * dashee::test::callExit(void * nothing)
{
    UNUSED(nothing);
    dashee::Threads::Thread::exit();
    CPPUNIT_ASSERT(true);
    return NULL;
}

/** 
 * This function will take in a v, and run a a loop n times
 * This loop adds an internally defined variable, which is used
 * 
 * @param v the value to call exit with
 *
 * @returns a pointer of the value that came in
 */ 
void * dashee::test::exitValue(void * v)
{
    dashee::Threads::Thread::exit(v);

    return v;
}

/**
 * This will test our scope locks using the RAII strategy
 *
 * @param v The lock value to scope lock
 *
 * @return NULL
 */
void * dashee::test::scopeLocks(void * v)
{
    dashee::Threads::Scope(static_cast<dashee::Threads::Lock *>(v));

    // Do nothing for a while, so other threads can 
    // try to fight for locks
    for (int x = 0; x < 100; x++)
    {
	dashee::test::sharedVariable++;
	sleep(100);
    }

    return NULL;
}

/**
 * Try double locking threads, and try to recover.
 *
 * This will fail in a non conventional way, The failure is 
 * detected by the thread never coming out of lock in some cases
 *
 * So the only way you know it passed, is that if the test finished.
 *
 * Its not ideal but it is better than nothing, completely open to new 
 * ideas
 *
 * @param l The lock that was passed
 *
 * @returns Nothing
 */ 
void * dashee::test::doubleLock(void * l)
{
    dashee::Threads::Lock * lock 
        = static_cast<dashee::Threads::Lock *>(l);

    try
    {
        // Do nothing for a while, so other threads can 
        // try to fight for locks
        for (int x = 0; x < 100; x++)
        {
            lock->lock(dashee::Threads::Lock::LOCKTYPE_WRITE);
            lock->lock(dashee::Threads::Lock::LOCKTYPE_WRITE);
            
            dashee::test::sharedVariable++;
            sleep(100);

            lock->unlock();
        }
    }
    catch (dashee::Threads::Exception ex)
    {
        lock->unlock();
    }
    
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
    this->thread->start(static_cast<void *>(NULL));
    this->thread->join();

    delete this->thread;
}

/**
 * You can't start a thread twice asynchronously but you can do it 
 * synchronously.
 */
void dashee::test::Threads::testMultiStarts()
{
    this->thread = new dashee::Threads::Thread(donothing);
    this->thread->start(static_cast<void *>(NULL));
    this->thread->join();
    CPPUNIT_ASSERT(true);

    this->thread->start(static_cast<void *>(NULL));
    this->thread->join();
    CPPUNIT_ASSERT(true);
    
    this->thread->start(static_cast<void *>(NULL));
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
    this->thread->start(static_cast<void *>(NULL));
    this->thread->join();

    delete this->thread;
}

/**
 * Simple thread just runs callSelf, which is asserted
 */
void dashee::test::Threads::testExits()
{
    // A simple exit call
    this->thread = new dashee::Threads::Thread(callExit);
    this->thread->start(static_cast<void *>(NULL));
    this->thread->join();
    delete this->thread;

    // Call exit within the thread and read the value that join returns
    int * x = new int(20);
    int * retval;

    // Ensure our x is set correctly
    CPPUNIT_ASSERT(*x == 20);

    // Run our thread, and pass x
    this->thread = new dashee::Threads::Thread(exitValue);
    this->thread->start(static_cast<void *>(x));

    // Call join and set retval to take the returned value
    // ensure the value is good, and retval points to x
    retval = static_cast<int *>(this->thread->join());
    CPPUNIT_ASSERT(*retval == 20);
    CPPUNIT_ASSERT(retval == x);

    delete x;
    delete this->thread;
}

/**
 * Test Adding to sharedVariable using locking, locks are passed in as value
 */
void dashee::test::Threads::testLock()
{
    CPPUNIT_ASSERT(sharedVariable == 0);

    dashee::Threads::Thread * t1 = new dashee::Threads::Thread(addNTimes);
    dashee::Threads::Thread * t2 = new dashee::Threads::Thread(addNTimes);
    dashee::Threads::Thread * t3 = new dashee::Threads::Thread(addNTimes);
    dashee::Threads::Thread * t4 = new dashee::Threads::Thread(addNTimes);

    t1->start(&lockReadWrite);
    t2->start(&lockReadWrite);
    t3->start(&lockReadWrite);
    t4->start(&lockReadWrite);

    t1->join();
    t2->join();
    t3->join();
    t4->join();
    
    CPPUNIT_ASSERT(sharedVariable == 400);
    
    t1->start(&lockMutex);
    t2->start(&lockMutex);
    t3->start(&lockMutex);
    t4->start(&lockMutex);
    
    t1->join();
    t2->join();
    t3->join();
    t4->join();

    CPPUNIT_ASSERT(sharedVariable == 800);

    t1->start(&lockMutex);
    t2->start(&lockMutex);
    t3->start(&lockMutex);
    t4->start(&lockMutex);
    
    t1->join();
    t2->join();
    t3->join();
    t4->join();
    
    CPPUNIT_ASSERT(sharedVariable == 1200);
    sharedVariable = 0;

    delete t1;
    delete t2;
    delete t3;
    delete t4;
}

/**
 * Test double locking write and read, All locks should fail and leave the 
 * sharedVariable untouched
 */ 
void dashee::test::Threads::testDoubleLock()
{
    sharedVariable = 0;

    dashee::Threads::Thread * t1 = new dashee::Threads::Thread(doubleLock);
    dashee::Threads::Thread * t2 = new dashee::Threads::Thread(doubleLock);
    dashee::Threads::Thread * t3 = new dashee::Threads::Thread(doubleLock);

    t1->start(&lockReadWrite);
    t2->start(&lockReadWrite);
    t3->start(&lockReadWrite);
    
    t1->join();
    t2->join();
    t3->join();
    
    CPPUNIT_ASSERT(sharedVariable == 0);
    
    delete t1;
    delete t2;
    delete t3;
}

/**
 * This will call the scope Locks function which adds 100 to the value of 
 * shared variable
 */
void dashee::test::Threads::testScopeLock()
{
    sharedVariable = 0;
    CPPUNIT_ASSERT(sharedVariable == 0);

    dashee::Threads::Thread * t1 = new dashee::Threads::Thread(addNTimes);
    dashee::Threads::Thread * t2 = new dashee::Threads::Thread(addNTimes);
    dashee::Threads::Thread * t3 = new dashee::Threads::Thread(addNTimes);
    dashee::Threads::Thread * t4 = new dashee::Threads::Thread(addNTimes);

    t1->start(&lockReadWrite);
    t2->start(&lockReadWrite);
    t3->start(&lockReadWrite);
    t4->start(&lockReadWrite);

    t1->join();
    t2->join();
    t3->join();
    t4->join();
    
    CPPUNIT_ASSERT(sharedVariable == 400);
    
    t1->start(&lockMutex);
    t2->start(&lockMutex);
    t3->start(&lockMutex);
    t4->start(&lockMutex);
    
    t1->join();
    t2->join();
    t3->join();
    t4->join();

    CPPUNIT_ASSERT(sharedVariable == 800);

    t1->start(&lockMutex);
    t2->start(&lockMutex);
    t3->start(&lockMutex);
    t4->start(&lockMutex);
    
    t1->join();
    t2->join();
    t3->join();
    t4->join();
    
    CPPUNIT_ASSERT(sharedVariable == 1200);
    sharedVariable = 0;

    delete t1;
    delete t2;
    delete t3;
    delete t4;
}
/**
 * This function should throw an exception because a thread must only be 
 * started once
 */
void dashee::test::Threads::testCallingOneStartOnly()
{
    this->thread = new dashee::Threads::Thread(donothing);
    this->thread->start(static_cast<void *>(NULL));
    this->thread->start(static_cast<void *>(NULL));
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
