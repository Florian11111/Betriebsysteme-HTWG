#include <stdlib.h>

int main() {
    int* ptr = (int*)malloc(sizeof(int));
    *ptr = 5;
    return 0;
}