#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int nachricht = 0;
    int pipefd[2]; // pipeline

    if (pipe(pipefd) == -1) {
        fprintf(stderr, "pipe failed\n");
        exit(1);
    }

    int rc1 = fork();
    if (rc1 < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc1 == 0) {
        close(pipefd[0]);
        printf("%s\n", "Nachricht an rc2 nachricht: 5!");
        nachricht = 5;
        write(pipefd[1], &nachricht, sizeof(nachricht));
        close(pipefd[1]);
        exit(0);
    }

    int rc2 = fork();
    if (rc2 < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc2 == 0) {
        close(pipefd[1]);
        read(pipefd[0], &nachricht, sizeof(nachricht));
        printf("Nachricht von rc1: %d\n", nachricht);
        close(pipefd[0]);
        exit(0);
    }

    return 0;
}
