#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#include <dashee/Thread.h>

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;

int x = 0;

void * work(void * ptr);

int main()
{
    std::string * t1name = new std::string("t1");
    std::string * t2name = new std::string("t2");

    pthread_t t1;
    pthread_t t2;

    pthread_create(&t1, NULL, work, reinterpret_cast<void *>(t1name));
    pthread_create(&t2, NULL, work, reinterpret_cast<void *>(t1name));

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    std::cout << "Thread t1 id: " << t1 << std::endl;
    std::cout << "Thread t2 id: " << t2 << std::endl;


    /**
    dashee::Thread t1(work);
    dashee::Thread t2(work);
    int returnt1, returnt2;


    t1.start(reinterpret_cast<void *>(t1name));
    t2.start(reinterpret_cast<void *>(t2name));

    t1.join();
    t2.join();

    */
    
    delete t1name;
    delete t2name;

    std::cout << "Finishing things" << std::endl;

    return 0;
}

void * work(void * ptr)
{
    for (int c = 0; c < 100 && x < 100; c++)
    {
	pthread_mutex_lock(&m1);
        x++;
	std::cout << *(reinterpret_cast<std::string *>(ptr)) << 
            " changing x to " << x << std::endl;
	pthread_mutex_unlock(&m1);

	usleep(rand() % 10000);
    }
}
