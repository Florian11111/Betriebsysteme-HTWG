#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("%d parameter: ", argc);
    for (int i = 0; i < argc; i++) {
        printf("%s   ", argv[i]);
    }
    printf("\n");
    return 0;
}
