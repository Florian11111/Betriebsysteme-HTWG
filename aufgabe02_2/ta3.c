#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int warte = 0;
    int pipefd[2]; // pipline

    if (pipe(pipefd) == -1) {
        fprintf(stderr, "pipe failed\n");
        exit(1);
    }

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("%s\n", "hello");
        write(pipefd[1], &warte, sizeof(warte));
    } else {
        // der code wartet hier bis etwas in die pipline geschrieben wird
        read(pipefd[0], &warte, sizeof(warte));
        printf("%s\n", "goodbye");
    }
    return 0;
}

