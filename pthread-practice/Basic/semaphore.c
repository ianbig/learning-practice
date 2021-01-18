/**
 * Testing correctness and proficiencty of semaphore
 * Testing lock ouside function
 * Test assign to local variable
**/
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

#define DIS_NUM 1000000000

unsigned long int global = 0;
sem_t semaphores;

void add_huge_num() {
    int i = 0;
    int local_sum = 0;
    
    // sem_wait(&semaphores);
    for(i = 0; i < DIS_NUM; i++) {
        /** section for lock global value on each access **/
        // sem_wait(&semaphores);
        // global += 1;
        // sem_post(&semaphores);

        /** section for add up value then assign to global value **/
        local_sum += 1;
    }
    // sem_post(&semaphores);

    sem_wait(&semaphores);
    fprintf(stderr, "After locking: %d\n", semaphores);
    global += local_sum;
    sem_post(&semaphores);
    // sem_post(&semaphores);
    // sem_post(&semaphores);
    fprintf(stderr, "After unlock: %d\n", semaphores);
}

int main(int argc, char **argv) {
    pthread_t tid_1, tid_2;
    
    sem_init(&semaphores, 0, 1);
    pthread_create(&tid_1, NULL, (void *)add_huge_num, NULL);
    pthread_create(&tid_2, NULL, (void *)add_huge_num, NULL);
    pthread_join(tid_1, NULL);
    pthread_join(tid_2, NULL);
    
   // add_huge_num();
   printf("Semaphore: 1000000000 + 1000000000 = %ld\n", global);

    return 0;
}