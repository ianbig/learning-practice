/** resolve deadlock 
 * use traditional semaphore solution
 * need mutex lock to preserve the integrity of buffer
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define MAX_BUFFER_SIZE 100
#define THREAD_SHARED 0

enum {
    OFF,
    ON
};

int buffer[MAX_BUFFER_SIZE] = {0};
sem_t capacity;
sem_t itemCount;
int in = 0, out = 0;
pthread_mutex_t mutex_for_buffer;

enum {
    PRODUCER,
    CONSUMER,
};

void consumer() {
    for(int i = 0; 1; i++) {
        sem_wait(&itemCount); // sleep consumer
        pthread_mutex_lock(&mutex_for_buffer);
        fprintf(stderr, "Consumer consume items: %d\n", buffer[out]);
        out = (out + 1) % MAX_BUFFER_SIZE;
        pthread_mutex_unlock(&mutex_for_buffer);
        sem_post(&capacity); // wake producer
    }
}

void producer() {
    for(int i = 0; 1; i++) {
        sem_wait(&capacity); // capacity -= 1 if capacity == 0 sleep producer
        pthread_mutex_lock(&mutex_for_buffer);
        buffer[in] = rand();
        fprintf(stderr, "Producer produce items: %d\n", buffer[in]);
        in = (in + 1) % MAX_BUFFER_SIZE;
        pthread_mutex_unlock(&mutex_for_buffer);
        sem_post(&itemCount); // itemCount += 1 wake consumer
    }
}

int main(int argc, char **argv) {
    pthread_t consumer_thread, producer_thread;
    srand(1);

    sem_init(&capacity, THREAD_SHARED, MAX_BUFFER_SIZE);
    sem_init(&itemCount, THREAD_SHARED, 0);
    pthread_mutex_init(&mutex_for_buffer, NULL);

    pthread_create(&producer_thread, NULL, (void *)producer, NULL);
    pthread_create(&consumer_thread, NULL, (void *)consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
}