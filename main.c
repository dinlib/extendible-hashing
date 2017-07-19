#include <stdio.h>

#define MAX_SIZE 12

int hash(int);

typedef struct {
    int prof;
    int cont;
    int chaves[MAX_SIZE];
    int id;
} BUCKET;

typedef struct {
    BUCKET *bucket_ref;
} DIR_CELL;

typedef struct {
    int prof;
    DIR_CELL *celulas;
} DIRETORIO;

int make_address(int key, int prof) {
    int retval = 0;
    int mask = 1;
    int hashval = hash(key);
    
    for (int j = 0; j < prof; j++) {
        retval = retval << 1;
        int lowbit = hashval & mask;
        retval = retval | lowbit;
        hashval = hashval > 1;
    }

    return retval;
}

int main(int argc, const char *argv[]) {
    
    return 0;
}