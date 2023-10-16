#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>

int main() {
    int rc = fork();
    printf("execv: ");
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        char *myargs[] = { "./testAufruf", "testParameter1", NULL };
        execv(myargs[0], myargs);
        printf("Irgentwas ist Falsch gelaufen!");
    }

    return 0;
}
