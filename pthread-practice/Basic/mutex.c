/**
 * Testing correctness and proficiencty of mutex
 * Test mutex outside for loop: correct value
 * Test mutex around critical section: correct value
 * Test assign to local variable
**/

#include <pthread.h>
#include <stdio.h>

#define DIS_NUM 1000000000

unsigned long int global = 0;
pthread_mutex_t mutex;

void add_huge_num() {
    int i = 0;
    int local_sum = 0;

    // pthread_mutex_lock(&mutex);
    for(i = 0; i < DIS_NUM; i++) {
        //pthread_mutex_lock(&mutex);
        local_sum += 1;
        // pthread_mutex_unlock(&mutex);
    }
    // pthread_mutex_unlock(&mutex);

    pthread_mutex_lock(&mutex);
    global += local_sum;
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char **argv) {
    pthread_t tid_1, tid_2;
    
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&tid_1, NULL, (void *)add_huge_num, NULL);
    pthread_create(&tid_2, NULL, (void *)add_huge_num, NULL);
    pthread_join(tid_1, NULL);
    pthread_join(tid_2, NULL);
    
   // add_huge_num();
   printf("Mutex: 1000000000 + 1000000000 = %ld\n", global);

    return 0;
}