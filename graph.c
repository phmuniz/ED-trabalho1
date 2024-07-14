#include "graph.h"
#include "city.h"
#include "neighbor.h"
#include "vector.h"
#include <string.h>

struct Graph
{
    char algorithm[5];
    int start;
    int end;
    Vector * cities;
    void * border;
};

Graph * graph_construct(FILE * file){

    Graph * g = (Graph*)calloc(1, sizeof(Graph));

    g->cities = vector_construct();

    fscanf(file, "%s", g->algorithm);
    fscanf(file, "%d %d", &g->start, &g->end);

    int num_cities;
    fscanf(file, "%d", &num_cities);

    for (int i = 0; i < num_cities; i++)
    {      
        City * c = city_construct(file);
        vector_push_back(g->cities, c);
    }
    
    return g;
}

void graph_destroy(Graph * g){

    for (int i = 0; i < vector_size(g->cities); i++)
    {
        City * c = vector_get(g->cities, i);
        city_destroy(c);
    }

    vector_destroy(g->cities);

    free(g);
}

void graph_print(Graph * g){

    printf("ALGORITHM: %s\n", g->algorithm);
    printf("START: %d\n", g->start);
    printf("END: %d\n\n", g->end);

    for (int i = 0; i < vector_size(g->cities); i++)
    {
        printf("CITY %d\n", i);
        city_print(vector_get(g->cities, i));
        printf("\n");
    }
    
}