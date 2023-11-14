#include <stdio.h>
#include <stdlib.h>

#define ANZAHL_DURCHLAUFE 1000

typedef struct {
    int* data;
    size_t size;
} Vector;

void init(Vector* vector) {
    vector->data = NULL;
    vector->size = 0;
}

int push(Vector* vector, int element) {
    vector->size += 1;
    vector->data = (int*)realloc(vector->data, vector->size * sizeof(int));
    if (vector->data == NULL) {
        printf("realloc Failed!\n");
        return -1;
    }
    vector->data[vector->size - 1] = element;
    return 0;
}

void freeVector(Vector* vector) {
    free(vector->data);
    vector->size = 0;
}

void processMemory(int x) {
    Vector vector;
    init(&vector);
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < ANZAHL_DURCHLAUFE; j++) {
            if (push(&vector, i * 100) == -1) 
                printf("error!");
        }
    }
    freeVector(&vector);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Bitte geben Sie einen Wert für x an.\n");
        return 1;
    }

    long x = atoi(argv[1]);
    processMemory(x);
    printf("insgesamt: %ld Intiger werte!\n", ANZAHL_DURCHLAUFE * x);
    
    return 0;
}