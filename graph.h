#ifndef _GRAPH_H
#define _GRAPH_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Graph Graph;

typedef void (*push_fn)(void *, void *);
typedef void * (*pop_fn)(void *);
typedef int (*size_fn)(void *);
typedef void (*destroy_fn)(void *);

Graph * graph_construct(FILE * file);

void graph_data(Graph * g);

void graph_destroy(Graph * g);

void graph_print(Graph * g);

#endif