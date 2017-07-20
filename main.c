#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bucket.h"

int get_index(unsigned int address, int prof) {
    int n = 32 - prof;
    return address >> n;
}

int main(int argc, const char *argv[]) {
    char buffer[10];
    // init_dir();

    // while (fgets(buffer, 10, stdin)) {
    //     buffer[strlen(buffer) - 1] = '\0';
    //     int key = atoi(buffer);
    //     op_add(key);
    // }

    unsigned int address = make_address(236997u, PROF_ADDRESS);
    int index = get_index(address, 1);

    printf("%d\n", index);

    return 0;
}
