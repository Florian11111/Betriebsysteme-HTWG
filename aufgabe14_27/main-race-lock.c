#include <stdio.h>
#include "common_threads.h"

typedef struct __lock_t {
    int flag;
    int guard;
} lock_t;

void lock_init(lock_t *lock) {
    lock->flag = 0;
    lock->guard = 0;
}

void lock(lock_t *lock) {
    while (__sync_lock_test_and_set(&lock->guard, 1) == 1)
        ; 

    if (lock->flag == 0) {
        lock->flag = 1; 
        lock->guard = 0;
    } else {
        lock->guard = 0;
        while (lock->flag != 0)
            ; // spin
    }
}

void unlock(lock_t *lock) {
    __sync_lock_release(&lock->flag);
}

int balance = 0;
lock_t mylock; // global lock

void* worker(void* arg) {
    lock(&mylock);
    balance++;
    unlock(&mylock);
    return NULL;
}

int main(int argc, char *argv[]) {
    lock_init(&mylock);

    pthread_t p;
    Pthread_create(&p, NULL, worker, NULL);

    lock(&mylock);
    balance++;
    unlock(&mylock);

    Pthread_join(p, NULL);
    return 0;
}
