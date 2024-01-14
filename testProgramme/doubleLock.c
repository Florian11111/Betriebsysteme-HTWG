#include <stdio.h>
#include <pthread.h>

int main() {
    pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;

    // Erster Lock
    pthread_mutex_lock(&myMutex);
    printf("Mutex gesperrt (1. Lock).\n");

    // Zweiter Lock (ungültig und kann zu einem Deadlock führen)
    pthread_mutex_lock(&myMutex);
    printf("Mutex erneut gesperrt (2. Lock).\n");

    pthread_mutex_unlock(&myMutex);

    printf("Programm beendet.\n");

    return 0;
}
