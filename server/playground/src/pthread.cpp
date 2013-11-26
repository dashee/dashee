#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;

int x = 0;

void * work(void * ptr);

int main()
{
    pthread_t t1, t2;
    int returnt1, returnt2;

    std::string * t1name = new std::string("t1");
    std::string * t2name = new std::string("t2");

    pthread_create(&t1, NULL, work, reinterpret_cast<void *>(t1name));
    pthread_create(&t2, NULL, work, reinterpret_cast<void *>(t2name));

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

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

	usleep(rand() % 1000000);
    }
}
