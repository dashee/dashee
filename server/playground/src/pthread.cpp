#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#include <dashee/Thread.h>
#include <dashee/Lock/Mutex.h>
#include <dashee/Lock/ReadWrite.h>

dashee::LockReadWrite readLock = dashee::LockReadWrite();
dashee::LockReadWrite writeLock 
    = dashee::LockReadWrite(dashee::LockReadWrite::LOCKTYPE_WRITE);

int x = 0;

void * work(void * ptr);

int main()
{
    std::string * t1name = new std::string("t1");
    std::string * t2name = new std::string("t2");

    dashee::Thread t1(work);
    dashee::Thread t2(work);

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

    readLock.unlock();
}
