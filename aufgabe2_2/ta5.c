#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int test = wait(NULL);
    printf("wait ohne child process: %d\n", test);
    printf("hello, I am Parant (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        int test2 = wait(NULL);
        printf("wait in child process: %d\n", test2);
    } else {
        // wait returnd die processid vom Kind process
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d)\n", rc, wc);
    }
    return 0;
}
