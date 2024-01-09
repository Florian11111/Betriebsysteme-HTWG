#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main() {
    struct timeval start, end;

    gettimeofday(&start, NULL);

    //sleep(1);

    gettimeofday(&end, NULL);

    long long zeit = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

    printf("%lld micros. \n", zeit);

    return 0;
}
