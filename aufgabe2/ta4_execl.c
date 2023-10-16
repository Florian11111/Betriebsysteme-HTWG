#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>

int main() {
    int rc = fork();
    printf("execl: ");
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        char *myargs[] = { "./testAufruf", "testParameter1", NULL };
        execl(myargs[0], myargs[0], myargs[1], NULL);
        /* 
             execl(myargs[0], myargs[1], myargs[2], NULL);
            geht auch ruft das programm aber ohne den namen als argument auf
        */
        printf("Irgentwas ist Falsch gelaufen!");
    }

    return 0;
}
