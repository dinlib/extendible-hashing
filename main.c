#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bucket.h"

int main(int argc, const char *argv[]) {
    char buffer[10];
    FILE *file = fopen("chaves.txt", "r");
    init_dir();

    while (!feof(file)) {
        fgets(buffer, 10, file);
        int key = atoi(buffer);
        op_add(key);
    }

    print_dir();

    return 0;
}