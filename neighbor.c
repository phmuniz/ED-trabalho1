#include "neighbor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Neighbor{
    int idx;
    int dist;
};

Neighbor * neighbor_construct(FILE * file){

    Neighbor * n = (Neighbor*)calloc(1, sizeof(Neighbor));

    fscanf(file, "%d %d", &n->idx, &n->dist);

    return n;
}

int neighbor_idx(Neighbor * n){
    return n->idx;
}

void neighbor_destroy(Neighbor * n){
    free(n);
}

void neighbor_print(Neighbor * n){

    printf("IDX_NEIGHBOR: %d\n", n->idx);
    printf("DISTANCE_TO_ORIGIN: %d\n", n->dist);
}