#ifndef _GRAPH_H
#define _GRAPH_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Graph Graph;

Graph * graph_construct(FILE * file);

void graph_data(Graph * g);

void graph_destroy(Graph * g);

void graph_print(Graph * g);

#endif