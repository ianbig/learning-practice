/** a race condidtion cause a deadlock situation**/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 100

enum {
    OFF,
    ON
};

int buffer[MAX_BUFFER_SIZE] = {0};
int itemCounts = 0;

int consumer_thread_status = ON;
int producer_thread_status = OFF;

enum {
    PRODUCER,
    CONSUMER,
};

int putItems(int item) {
    buffer[itemCounts] = item;
    return item;
}

int retrevieItem() {
    return buffer[itemCounts];
}

void mysleep(int type) {
    if(type == PRODUCER) {
        fprintf(stderr, "producer is sleeping\n");
        producer_thread_status = OFF;
        while(producer_thread_status == OFF);
    } else if(type == CONSUMER) {
        fprintf(stderr, "consumer is sleeping\n");
        consumer_thread_status = OFF;
        while(consumer_thread_status == OFF);
    }
}

void wake(int type) {
    if(type == PRODUCER) {
        fprintf(stderr, "producer is waking\n");
        producer_thread_status = ON;
    } else if(type == CONSUMER) {
        fprintf(stderr, "consumer is waking\n");
        consumer_thread_status = ON;
    }
}

void consumer() {
    while(1) {
        if(itemCounts == 0) {
            mysleep(CONSUMER); // psedo
        }
        fprintf(stderr, "Consumer retrieve item %d\n", retrevieItem());
        itemCounts -= 1;

        if(itemCounts == MAX_BUFFER_SIZE - 1) {
            wake(PRODUCER);
        }
    }
}

void producer() {
    int index = 100;
    while(1) {
        /*
        if(index == 200) {
            fprintf(stderr, "Procuder finish producing\n");
            return;
        }
        */
        if(itemCounts == MAX_BUFFER_SIZE) {
            mysleep(PRODUCER);
        }
        fprintf(stderr, "Producer produce item %d\n", putItems(index));
        index += 1;
        itemCounts += 1;

        if(itemCounts == 1) {
            wake(CONSUMER);
        }
    }
}

int main(int argc, char **argv) {
    pthread_t consumer_thread, producer_thread;

    pthread_create(&producer_thread, NULL, (void *)producer, NULL);
    // sleep(0.01);
    pthread_create(&consumer_thread, NULL, (void *)consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
}