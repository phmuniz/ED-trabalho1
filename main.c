#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    FILE * file = fopen("entrada.txt", "r");

    Graph * g = graph_construct(file);

    graph_data(g);

    fclose(file);
    graph_destroy(g);

    return 0;
}