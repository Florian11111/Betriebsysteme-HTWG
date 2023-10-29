#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Bitte 2 argumente!\n");
        return 1;
    }
    printf("process ID: %d\n", getpid());
    int i = atoi(argv[1]);
    int anzahlDurchlaufe = atoi(argv[2]);

    if (i <= 0) {
        printf("Invalid input. Please provide a positive integer for the number of megabytes.\n");
        return 1;
    }

    long long num_elements = (i * 1000000000LL) / sizeof(int);
    int *arr = (int*)malloc(num_elements * sizeof(int));

    if (arr == NULL) {
        printf("allocate Failed!\n");
        return -1;
    }

    for (long long i = 0; i < num_elements; i++) {
        arr[i] = 1;
    }

    for (int i = 0; i < anzahlDurchlaufe; i++) {
        for (long long i = 0; i < num_elements; i++) {
            arr[i]++;
        }
    }
    free(arr);

    return 0;
}
