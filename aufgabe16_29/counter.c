#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct __counter_t {
    int value;
    pthread_mutex_t lock;
} counter_t;

void init(counter_t *c) {
    c->value = 0;
    pthread_mutex_init(&c->lock, NULL);
}
void increment(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    c->value++;
    pthread_mutex_unlock(&c->lock);
}
void decrement(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    c->value--;
    pthread_mutex_unlock(&c->lock);
}
int get(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    int rc = c->value;
    pthread_mutex_unlock(&c->lock);
return rc;
}


void *count(void *arg) {
    int countTO = 10000000 / 1;
    counter_t *counter = (counter_t *)arg;
    for (int i = 0; i < countTO; ++i) {
        increment(counter);
    }
    return NULL;
}

int main() {
    int ANZAHL_THREADS = 1;
    counter_t counter;
    init(&counter);

    struct timeval start, end;
    gettimeofday(&start, NULL);

    pthread_t threads[ANZAHL_THREADS];

    for (int i = 0; i < ANZAHL_THREADS; ++i) {
        pthread_create(&threads[i], NULL, count, &counter);
    }

    for (int i = 0; i < ANZAHL_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end, NULL);
    long long zeit = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    printf("gesamt: %d hat mit %d threads: %lld microsecunden gebraucht\n", get(&counter), ANZAHL_THREADS, zeit);

    return 0;
}
