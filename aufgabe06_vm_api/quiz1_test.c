#include <stdio.h>

    int main(int argc, char const *argv[])
    {
        int *x = (int*) malloc(sizeof(int));
        printf("x: %d\n",*x);
        return 0;
    }