#include "graph.h"
#include "city.h"
#include "neighbor.h"
#include "vector.h"
#include "dfs.h"
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

    if(!strcmp(g->algorithm, "DFS")) g->border = dfs_construct();
    
    return g;
}

void graph_data(Graph * g){

    City * city_origin = vector_get(g->cities, g->start);

    if(!strcmp(g->algorithm, "DFS")) dfs_push(g->border, city_origin);

    City * city_selected;
    int size = 1;

    while(size != 0){

        if(!strcmp(g->algorithm, "DFS")) city_selected = (City *)dfs_pop(g->border);

        if(city_idx(city_selected) == g->end) break;

        if(!city_viseted(city_selected)){

            for (int i = 0; i < city_num_neighbors(city_selected); i++){
                
                Neighbor * n = city_get_neighbor(city_selected, i);
                City * city_neighbor = vector_get(g->cities, neighbor_idx(n));

                if(!city_viseted(city_neighbor)){
                    city_set_dad(city_neighbor, city_idx(city_selected));
                    if(!strcmp(g->algorithm, "DFS")) dfs_push(g->border, city_neighbor);
                }
            }

            city_set_viseted(city_selected);
        }

        if(!strcmp(g->algorithm, "DFS")) size = dfs_size(g->border);
    }

    if(city_idx(city_selected) == g->end){
        Vector * path = vector_construct();
        vector_push_back(path, city_selected);
        City * city_current = city_selected;

        while (1){
            
            City * city_dad = vector_get(g->cities, city_get_dad(city_current));

            vector_push_back(path, city_dad);

            if(city_idx(city_dad) == g->start) break;

            city_current = city_dad;
        }

        printf("CAMINHO:\n");

        for (int i = vector_size(path) - 1; i >= 0; i--){
            
            city_current = vector_get(path, i);

            printf("%s", city_name(city_current));
            if(i != 0) printf(" -> ");
        }
        
        vector_destroy(path);
    }
    else printf("GRAFO NÃO CONECTADO\n");
}

void graph_destroy(Graph * g){

    for (int i = 0; i < vector_size(g->cities); i++)
    {
        City * c = vector_get(g->cities, i);
        city_destroy(c);
    }

    vector_destroy(g->cities);

    if(!strcmp(g->algorithm, "DFS")) dfs_destroy(g->border);

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