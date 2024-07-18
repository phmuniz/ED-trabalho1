#include "bfs.h"
#include "deque.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Bfs
{
    Deque * f;
};

Bfs *bfs_construct(){

    Bfs * b = (Bfs*)calloc(1, sizeof(Bfs));

    b->f = deque_construct();

    return b;
}
void bfs_push(void *b, void * item){

    Bfs * bfs = (Bfs *)b;

    deque_push_back(bfs->f, item);
}
void *bfs_pop(void *b){

    Bfs * bfs = (Bfs *)b;

    return deque_pop_front(bfs->f);
}

int bfs_size(void *b){
    Bfs * bfs = (Bfs *)b;

    return deque_size(bfs->f);
}

void bfs_destroy(void *b){

    Bfs * bfs = (Bfs *)b;

    deque_destroy(bfs->f);
    free(bfs);
}