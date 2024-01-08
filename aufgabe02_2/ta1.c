#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // testvariable 
    int x = 100;

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("x (Child Orginal): %d\n", x);
        x = x * 5;
        printf("x (Child Veraendert): %d\n", x);
        return 0;
    } else {
        printf("x (Parant Orginal): %d\n", x);
        x = x / 5;
        printf("x (Parant Veraendert): %d\n", x);
    }
    return 0;
}

