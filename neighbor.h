#ifndef _NEIGHBOR_H_
#define _NEIGHBOR_H_

#include <stdio.h>

typedef struct Neighbor Neighbor;

Neighbor * neighbor_construct(FILE * file);

int neighbor_idx(Neighbor * n);

float neighbor_distance(Neighbor * n);

void neighbor_destroy(Neighbor * n);

void neighbor_print(Neighbor * n);

#endif