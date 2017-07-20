#ifndef BUCKET_H
#define BUCKET_H

#include "constants.h"

typedef struct {
    int prof;
    int cont;
    int chaves[MAX_BK_SIZE];
    int id;
} BUCKET;

typedef struct {
    BUCKET *bucket_ref;
} DIR_CELL;

typedef struct {
    int prof;
    int size;
    DIR_CELL *celulas;
} DIRETORIO;

void init_dir();
unsigned int make_address(unsigned int key, int prof);
BUCKET * op_find(int key);
void bk_add_key(BUCKET *bucket_found, int key);
void op_add(int key);

#endif