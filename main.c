#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bucket.h"

int main(int argc, const char *argv[]) {
    char buffer[10];
    FILE *file = fopen("chaves.txt", "r");
    init_dir();

    while (fgets(buffer, 10, file)) {
        buffer[strlen(buffer) - 1] = '\0';
        int key = atoi(buffer);
        op_add(key);
    }

    print_dir();

    return 0;
}
