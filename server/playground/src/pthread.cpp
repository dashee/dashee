#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;

int * x = new int(1);

void * work(void * ptr);

int main()
{
    pthread_t t1, t2;
    int returnt1, returnt2;

    pthread_create(&t1, NULL, work, reinterpret_cast<void *>(x));
    pthread_create(&t2, NULL, work, reinterpret_cast<void *>(x));

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    std::cout << "Finishing things" << std::endl;

    delete x;
    return 0;
}

void * work(void * ptr)
{
    for (int c = 0; c < 10000; c++)
    {
	pthread_mutex_lock(&m1);
	int * x = reinterpret_cast<int *>(ptr);

	std::cout << "Value of x is " << *x << std::endl;
	(*x)++;
	pthread_mutex_unlock(&m1);

	usleep(rand() % 100000);
    }
}
