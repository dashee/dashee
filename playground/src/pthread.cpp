#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#include <dashee/Threads/Thread.h>
#include <dashee/Threads/Lock/Mutex.h>
#include <dashee/Threads/Lock/ReadWrite.h>


dashee::Threads::LockMutex mutexLock = dashee::Threads::LockMutex();
dashee::Threads::LockReadWrite readLock = dashee::Threads::LockReadWrite();
dashee::Threads::LockReadWrite writeLock 
    = dashee::Threads::LockReadWrite(
            dashee::Threads::LockReadWrite::LOCKTYPE_WRITE
        );

int x = 0;

void * work(void * ptr);

int main()
{
    std::string * t1name = new std::string("t1");
    std::string * t2name = new std::string("t2");

    dashee::Threads::Thread t1(work);
    dashee::Threads::Thread t2(work);

    t1.start(reinterpret_cast<void *>(t1name));
    t2.start(reinterpret_cast<void *>(t2name));

    t1.join();
    t2.join();

    delete t1name;
    delete t2name;

    std::cout << "Finishing things" << std::endl;

    return 0;
}

void * work(void * ptr)
{
    try
    {
        readLock.lock();

        for (int c = 0; c < 1000 && x < 1000; c++)
        {
            writeLock.lock();
            x++;
            std::cout << *(reinterpret_cast<std::string *>(ptr)) << 
                " changing x to " << x << std::endl;
            writeLock.unlock();

            usleep(rand() % 1000);
        }

        mutexLock.unlock();
        readLock.unlock();

    }
    catch(dashee::Threads::ExceptionLock ex)
    {
        std::cout << ex.what() << std::endl;
    }
        
    mutexLock.unlock();
    writeLock.unlock();
    readLock.unlock();

    dashee::Threads::Thread::exit();
}
