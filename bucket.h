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
void op_add(int key);
void print_dir();

#endif