#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/wait.h>

int main() {
    int rc = fork();
    printf("execlp: ");
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        char *myargs[] = { "./testAufruf", "testParameter1", NULL };
        execlp(myargs[0], myargs[0], myargs[1], NULL);
        /* 
            execlp muss nicht der genau pfad angegeben werden. es reicht der name 
            das programm wird durch die Umgebungsvariable gefunden.
        */
        printf("Irgentwas ist Falsch gelaufen!");
    }

    return 0;
}
