#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("hello, I am Parant (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("hello, I am child (pid:%d)\n", (int) getpid());
    } else {
        // wait returnd die processid vom Kind process
        int status;
        int wc = waitpid(rc, &status, 0); // wartet nur auf das child rc. sonst würde es einfach auf das erste child warten
        printf("wait: %d\n", wc);
    }
    return 0;
}
