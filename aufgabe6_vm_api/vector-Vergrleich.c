#include <stdio.h>
#include <stdlib.h>

#define ANZAHL_DURCHLAUFE 1000

void processMemory(int x) {
    for (int i = 0; i < x; i++) {
        int* values = (int*)malloc(ANZAHL_DURCHLAUFE * sizeof(int));

        if (values == NULL) {
            printf("Speicherreservierung fehlgeschlagen.\n");
            return;
        }

        for (int j = 0; j < ANZAHL_DURCHLAUFE; j++) {
            values[j] = j * 10;
        }
        free(values);
    }
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