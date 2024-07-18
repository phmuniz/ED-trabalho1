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
    float cost;
    int num_cities_visited;
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
        City * c = city_construct(file, i);
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

        if(city_idx(city_selected) == g->end){
            g->num_cities_visited++;
            break;
        }

        if(!city_viseted(city_selected)){

            for (int i = 0; i < city_num_neighbors(city_selected); i++){
                
                Neighbor * n = city_get_neighbor(city_selected, i);
                City * city_neighbor = vector_get(g->cities, neighbor_idx(n));

                if(!city_viseted(city_neighbor) && !city_get_in_border(city_neighbor)){
                    city_set_dad(city_neighbor, city_idx(city_selected));
                    city_set_dist_to_origin(city_neighbor, (city_get_dist_to_origin(city_selected) + neighbor_distance(n)));
                    city_set_in_border(city_neighbor);
                    if(!strcmp(g->algorithm, "DFS")) dfs_push(g->border, city_neighbor);
                }
            }

            city_set_viseted(city_selected);
            g->num_cities_visited++;
        }

        if(!strcmp(g->algorithm, "DFS")) size = dfs_size(g->border);
    }

    if(city_idx(city_selected) == g->end){
        Vector * path = vector_construct();
        vector_push_back(path, city_selected);
        City * city_current = city_selected;
        g->cost = city_get_dist_to_origin(city_selected);

        while (1){
            
            City * city_dad = vector_get(g->cities, city_get_dad(city_current));

            vector_push_back(path, city_dad);

            if(city_idx(city_dad) == g->start) break;

            city_current = city_dad;
        }

        for (int i = vector_size(path) - 1; i >= 0; i--){
            
            city_current = vector_get(path, i);

            printf("%s\n", city_name(city_current));
        }

        printf("Custo: %.2f Num_Expandidos: %d\n", g->cost, g->num_cities_visited);
        
        vector_destroy(path);
    }
    else printf("IMPOSSIVEL\n");
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