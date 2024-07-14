#include "dfs.h"
#include "deque.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Dfs
{
    Deque * f;
};

Dfs *dfs_construct(){

    Dfs * d = (Dfs*)calloc(1, sizeof(Dfs));

    d->f = deque_construct();

    return d;
}
void dfs_push(void *d, void * item){

    Dfs * dfs = (Dfs *)d;

    deque_push_back(dfs->f, item);
}
void dfs_pop(void *d, destroy_fn destroy){

    Dfs * dfs = (Dfs *)d;

    void * item = deque_pop_back(dfs->f);

    destroy(item);
}

void dfs_destroy(void *d){

    Dfs * dfs = (Dfs *)d;

    deque_destroy(dfs->f);
    free(dfs);
}