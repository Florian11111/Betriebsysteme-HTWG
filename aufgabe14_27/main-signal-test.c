#include <stdio.h>

#include "common_threads.h"

int done = 0;

void* worker(void* arg) {
    int temp = 1;
    for (int i = 0; i <= 1000000000; i++) {
        temp = temp * temp * temp;
    }
    printf("%d\n", temp);
    printf("this should print first\n");
    done = 1;
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    Pthread_create(&p, NULL, worker, NULL);
    int i = 0;
    while (done == 0) {
        i++;
    }
    printf("%d\n", i);
    printf("this should print last\n");
    return 0;
}
