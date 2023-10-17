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
        close(STDOUT_FILENO);
        printf("das hier wird nicht ausgegeben!");
    } else {
        wait(NULL); 
        printf("das hier wird ausgegeben!\n");
    }
    printf("das hier wird nur vom Parant ausgegeben! (pid:%d)\n", (int) getpid());
    return 0;
}
