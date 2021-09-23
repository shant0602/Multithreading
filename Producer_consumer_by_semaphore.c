// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#define BUFFSIZE 10
#define THREAD_NUM 2
sem_t semprod, semcons;
pthread_mutex_t mx;
int buffer[BUFFSIZE];
int count = 0;
void *producer()
{
    while (1)
    {
        int x = rand() % 100;
        sem_wait(&semprod);
        sleep(1); //producer taking time to produce
        pthread_mutex_lock(&mx);
        // if (count < BUFFSIZE)
        // {
        buffer[count] = x;
        ++count;
        // }
        pthread_mutex_unlock(&mx);
        sem_post(&semcons);
    }
}

void *consumer()
{
    while (1)
    {
        int y = -1;
        sem_wait(&semcons);
        sleep(2); //producer taking time to produce
        pthread_mutex_lock(&mx);
        // if (count > 0)
        // {
        y = buffer[count - 1];
        --count;
        // }
        pthread_mutex_unlock(&mx);
        sem_post(&semprod);
        // sleep(1);
        printf("consumed %d\n", y);
    }
}

int main()
{
    srand(time(NULL));
    // Write C code here
    sem_init(&semprod, 0, BUFFSIZE);
    sem_init(&semcons, 0, 0);
    pthread_mutex_init(&mx, NULL);
    pthread_t t[THREAD_NUM];
    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (i & 1) //odd
            pthread_create(t + i, NULL, &consumer, NULL);
        else
            pthread_create(t + i, NULL, &producer, NULL);
    }
    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(t[i], NULL) != 0)
            perror("Error joining thread");
    }

    sem_destroy(&semprod);
    sem_destroy(&semcons);
    pthread_mutex_destroy(&mx);
    return 0;
}