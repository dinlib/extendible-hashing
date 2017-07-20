#include <stdlib.h>

#include "constants.h"
#include "bucket.h"

#define TRUE 1
#define FALSE 0

void bk_split(BUCKET *bucket);

DIRETORIO *dir;

void init_dir() {
    DIR_CELL *celulas;
    BUCKET *bucket;

    dir = (DIRETORIO*) malloc(sizeof(DIRETORIO));
    celulas = (DIR_CELL*) malloc(sizeof(DIR_CELL));
    bucket = (BUCKET*) malloc(sizeof(BUCKET));

    bucket->prof = 0;
    bucket->cont = 0;
    bucket->id = 0;

    celulas->bucket_ref = bucket;
    dir->prof = 0;
    dir->celulas = celulas;
    dir->size = 1;
}

unsigned int make_address(unsigned int key, int prof) {
    unsigned int retval = 0;
    unsigned int mask = 1;
    unsigned int hashval = key;

    for (int j = 0; j < prof; j++) {
        retval = retval << 1;
        unsigned int lowbit = hashval & mask;
        retval = retval | lowbit;
        hashval = hashval >> 1;
    }
    return retval;
}

int bk_find(BUCKET *bucket, int key) {
    for (int i = 0; i < bucket->cont; i++) {
        if (bucket->chaves[i] == key)
            return TRUE;
    }
    return FALSE;
}

BUCKET * op_find(int key) {
    unsigned int address = make_address(key, dir->prof);
    BUCKET *found_bucket = dir->celulas[address].bucket_ref;
    if (bk_find(found_bucket, key) == TRUE) return found_bucket;
    return NULL;
}

void bk_add_key(BUCKET *bucket, int key) {
    if (bucket->cont < MAX_BK_SIZE)
        bucket->chaves[bucket->cont++] = key;
    else {
        bk_split(bucket);
        op_add(key);
    }
}

void bk_split(BUCKET *bucket) {}

void op_add(int key) {
    BUCKET *bucket_found = op_find(key);
    if (bucket_found)
        bk_add_key(bucket_found, key);
}