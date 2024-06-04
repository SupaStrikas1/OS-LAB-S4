// Producer-Consumer problem using Semaphores

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 4

#define PRODUCER_NUM 2
#define CONSUMER_NUM 1

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t mutex, empty, full;

void *producer(void *arg)
{
    int item;
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        item = rand() % 100;
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[in] = item;
        printf("\nProduced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;
        sem_post(&mutex);
        sem_post(&full);
        sleep(1);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    int item;
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        item = buffer[out];
        printf("\nConsumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        sem_post(&mutex);
        sem_post(&empty);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t producer_threads[PRODUCER_NUM], consumer_threads[CONSUMER_NUM];

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    for (int i = 0; i < PRODUCER_NUM; i++)
    {
        pthread_create(&producer_threads[i], NULL, producer, NULL);
    }

    for (int i = 0; i < CONSUMER_NUM; i++)
    {
        pthread_create(&consumer_threads[i], NULL, consumer, NULL);
    }

    for (int i = 0; i < PRODUCER_NUM; i++)
    {
        pthread_join(producer_threads[i], NULL);
    }

    for (int i = 0; i < CONSUMER_NUM; i++)
    {
        pthread_join(consumer_threads[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}