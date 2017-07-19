#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 12

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

void initialize(DIRETORIO* *dir){
    DIR_CELL *cell;
    BUCKET *bucket;

    *dir = (DIRETORIO*) malloc(sizeof(DIRETORIO));
    cell = (DIR_CELL*) malloc(sizeof(DIR_CELL));
    bucket = (BUCKET*) malloc(sizeof(BUCKET));

    bucket->prof = 0;
    bucket->cont = 0;
    bucket->id = 0;

    cell->bucket_ref = bucket;
    (*dir)->prof = 0;
    (*dir)->celulas = cell;

    printf("CONT = %d\n", cell->bucket_ref->cont); //Teste
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
        printf("HASH = %d | RET = %d\n", hashval, retval); //Teste
    }
    printf("RETVAL = %d\n", retval); //Teste
    return retval;
}

int main(int argc, const char *argv[]) {
    DIRETORIO *principal;

    make_address(3,3); //Teste
    initialize(&principal); //Teste
    printf("ProfDir = %d | ProfBuck = %d\n", principal->prof, principal->celulas->bucket_ref->prof); //Teste
    return 0;
}
