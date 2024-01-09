#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define NUMCPUS 4

typedef struct __counter_t {
    int global;
    pthread_mutex_t glock;
    int local[NUMCPUS];
    pthread_mutex_t llock[NUMCPUS];
    int threshold;
} counter_t;

void init(counter_t *c, int threshold) {
    c->threshold = threshold;
    c->global = 0;
    pthread_mutex_init(&c->glock, NULL);
    int i;
    for (i = 0; i < NUMCPUS; i++) {
        c->local[i] = 0;
        pthread_mutex_init(&c->llock[i], NULL);
    }
}

void update(counter_t *c, int threadID, int amt) {
    int cpu = threadID % NUMCPUS;
    pthread_mutex_lock(&c->llock[cpu]);
    c->local[cpu] += amt;
    if (c->local[cpu] >= c->threshold) {
        pthread_mutex_lock(&c->glock);
        c->global += c->local[cpu];
        pthread_mutex_unlock(&c->glock);
        c->local[cpu] = 0;
    }
    pthread_mutex_unlock(&c->llock[cpu]);
}

int get(counter_t *c) {
    pthread_mutex_lock(&c->glock);
    int val = c->global;
    pthread_mutex_unlock(&c->glock);
    return val;
}

typedef struct arg_struct {
    counter_t *counter;
    int threadNummer;
} arg_struct;

void *count(void *arg) {
    int countTO = 1000000;
    arg_struct *args = (arg_struct *)arg;
    counter_t *counter = args->counter;
    int threadNumber = args->threadNummer;
    for (int i = 0; i < countTO; ++i) {
        update(counter, threadNumber, 1);
    }
    free(arg);  // Freigeben des dynamisch allokierten Speichers
    return NULL;
}

int main() {
    int threshold = 64;
    counter_t counter;
    init(&counter, threshold);

    struct timeval start, end;
    gettimeofday(&start, NULL);

    int threadNumber = NUMCPUS;
    pthread_t threads[threadNumber];

    for (int i = 0; i < threadNumber; ++i) {
        arg_struct *args = (arg_struct *)malloc(sizeof(arg_struct));
        args->counter = &counter;
        args->threadNummer = i;
        pthread_create(&threads[i], NULL, count, args);
    }

    for (int i = 0; i < threadNumber; ++i) {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end, NULL);
    long long zeit = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    printf("gesamt: %d | threshold %d | %d threads | %lld microsecunden\n", get(&counter), threshold, threadNumber, zeit);

    return 0;
}