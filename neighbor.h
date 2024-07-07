#ifndef _NEIGHBOR_H_
#define _NEIGHBOR_H_

typedef struct Neighbor Neighbor;

Neighbor * neighbor_construct(int idx, int dist);

int neighbor_idx(Neighbor * n);

int neighbor_distance(Neighbor * n);

void neighbor_destroy(Neighbor * n);

#endif