/**
 * test pthread without any snychronization mechanism
 * test without pthread_join
**/

/**
 * need pthread_join to wait thread finish
 * after parallelism, take longer time --> huge overhead
**/

#include <pthread.h>
#include <stdio.h>

#define DIS_NUM 1000000000

unsigned long int global = 0;

void add_huge_num() {
    int i = 0;

    for(i = 0; i < 2 * DIS_NUM; i++) {
        global += 1;
    }
}

int main(int argc, char **argv) {
    /*
    pthread_t tid_1, tid_2;
    
    pthread_create(&tid_1, NULL, (void *)add_huge_num, NULL);
    pthread_create(&tid_2, NULL, (void *)add_huge_num, NULL);
    pthread_join(tid_1, NULL);
    pthread_join(tid_2, NULL);
    */
   add_huge_num();
   printf("Lock-Free: 1000000000 + 1000000000 = %ld\n", global);

    return 0;
}