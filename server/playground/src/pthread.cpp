#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#include <dashee/Thread.h>
#include <dashee/Mutex.h>

dashee::Mutex m1;
dashee::Mutex m2;

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
    for (int c = 0; c < 1000 && x < 1000; c++)
    {
        m1.lock();
        x++;
        m2.lock();
        std::cout << *(reinterpret_cast<std::string *>(ptr)) << 
            " changing x to " << x << std::endl;
        m2.unlock();
        m1.unlock();

	usleep(rand() % 1000);
    }
}
