#include <stdio.h>

#define MAX_SIZE 12

typedef struct {
    int next;
    int count;
    int keys[MAX_SIZE];
    int id;
} Bucket;

int main(int argc, const char *argv[]) {
    printf("Hello World\n");
    return 0;
}