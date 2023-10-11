#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int file = open("ta2_output.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (file == -1) {
        printf("Error opening file!\n");
        exit(1);
    }

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        for (int i = 0; i < 100; i++)
            write(file, "welt ", 5);
    } else {
        for (int i = 0; i <= 100; i++)
            write(file, "hallo ", 6);
    }
    return 0;
}

