#include <stdlib.h>
#include <stdio.h>
#include "constants.h"

#include "bucket.h"

int make_address(int key, int prof);
int bk_find(BUCKET *bucket, int key);
BUCKET * op_find(int key);
void bk_split(BUCKET *bucket);
void dir_double();
void find_new_range(BUCKET *bucket, int *new_start, int *new_end);
void dir_ins_bucket(BUCKET *bucket, int new_start, int new_end);
void redis_keys(BUCKET *bucket1, BUCKET *bucket2);

DIRETORIO *dir;

void print_dir() {
    printf("Directory:\n");
    for (int i = 0; i < dir->size; i++)
        printf("dir[%d] = bucket #%d", i, dir->celulas[i].bucket_ref->id);

    printf("\n");
}

void init_dir() {
    DIR_CELL *celulas;
    BUCKET *bucket;

    dir = malloc(sizeof(DIRETORIO));
    celulas = malloc(sizeof(DIR_CELL));
    bucket = malloc(sizeof(BUCKET));

    bucket->prof = 0;
    bucket->cont = 0;
    bucket->id = 0;

    celulas->bucket_ref = bucket;
    dir->prof = 0;
    dir->celulas = celulas;
    dir->size = 1;
}

int make_address(int key, int prof) {
    int retval = 0;
    int mask = 1;
    int hashval = key;

    for (int j = 0; j < prof; j++) {
        retval = retval << 1;
        int lowbit = hashval & mask;
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
    int address = make_address(key, dir->prof);
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

void bk_split(BUCKET *bucket) {
    if (bucket->prof == dir->prof)
        dir_double();

    BUCKET *new_bk = malloc(sizeof(BUCKET));
    BUCKET *end_new_bk = new_bk;

    int new_start, new_end;

    find_new_range(bucket, &new_start, &new_end);
    dir_ins_bucket(end_new_bk, new_start, new_end);
    bucket->prof++;
    new_bk->prof = bucket->prof;
    redis_keys(bucket, new_bk);
}

void op_add(int key) {
    BUCKET *bucket_found = op_find(key);
    if (bucket_found)
        bk_add_key(bucket_found, key);
}

void dir_double() {
    int new_size = dir->size * 2;
    DIRETORIO *new_dir = malloc(sizeof(DIRETORIO));
    new_dir->celulas = malloc(new_size * sizeof(DIR_CELL));
    new_dir->size = new_size;

    for (int i = 0; i < dir->size - 1; i++) {
        new_dir->celulas[2*i].bucket_ref = dir->celulas[i].bucket_ref;
        new_dir->celulas[2*i+1].bucket_ref = dir->celulas[i+1].bucket_ref;
    }

    free(dir);
    dir = new_dir;
    dir->prof++;
}

void find_new_range(BUCKET *bucket, int *new_start, int *new_end) {
    int mask = 1;
    int shared_address = make_address(bucket->chaves[0], bucket->prof);
    shared_address = shared_address << 1;
    shared_address = shared_address | mask;

    int bits_to_fill = dir->prof - (bucket->prof + 1);
    *new_start = *new_end = shared_address;

    for (int j = 1; j < bits_to_fill; j++) {
        *new_start = *new_start << 1;
        *new_end = *new_end << 1;
        *new_end = *new_end | mask;
    }
}

void dir_ins_bucket(BUCKET *bucket, int start, int end) {
    for (int j = start; j < end; j++)
        dir->celulas[j].bucket_ref = bucket;
}

void redis_keys(BUCKET *bucket1, BUCKET *bucket2) {
    int backup[bucket1->cont];
    for (int i = 0; i < bucket1->cont; i++) {
        backup[i] = bucket1->chaves[i];
        bucket1->chaves[i] = 0;
        bucket1->cont--;
    }
    for (int i = 0; i < bucket1->cont; i++) {
        op_add(backup[i]);
    }
}
