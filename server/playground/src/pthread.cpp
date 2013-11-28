#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

<<<<<<< HEAD
#include <dashee/Thread.h>
#include <dashee/Lock/Mutex.h>
#include <dashee/Lock/ReadWrite.h>

dashee::LockReadWrite readLock = dashee::LockReadWrite();
dashee::LockReadWrite writeLock 
    = dashee::LockReadWrite(dashee::LockReadWrite::LOCKTYPE_WRITE);

int x = 0;
=======
pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;

int * x = new int(1);
>>>>>>> master

void * work(void * ptr);

int main()
{
<<<<<<< HEAD
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

=======
    pthread_t t1, t2;
    int returnt1, returnt2;

    pthread_create(&t1, NULL, work, reinterpret_cast<void *>(x));
    pthread_create(&t2, NULL, work, reinterpret_cast<void *>(x));

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    std::cout << "Finishing things" << std::endl;

    delete x;
>>>>>>> master
    return 0;
}

void * work(void * ptr)
{
<<<<<<< HEAD
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
=======
    for (int c = 0; c < 10000; c++)
    {
	pthread_mutex_lock(&m1);
	int * x = reinterpret_cast<int *>(ptr);

	std::cout << "Value of x is " << *x << std::endl;
	(*x)++;
	pthread_mutex_unlock(&m1);

	usleep(rand() % 100000);
    }
>>>>>>> master
}
