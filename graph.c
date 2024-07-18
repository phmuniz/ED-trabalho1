#include "graph.h"
#include "city.h"
#include "neighbor.h"
#include "vector.h"
#include "deque.h"
#include "heap.h"
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
    push_fn border_push;
    pop_fn border_pop;
    size_fn border_size;
    destroy_fn border_destroy;
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

    if(!strcmp(g->algorithm, "DFS")){
        g->border = deque_construct();
        g->border_push = deque_push_back;
        g->border_pop = deque_pop_back;
        g->border_size = deque_size;
        g->border_destroy = deque_destroy;
    } 
    if(!strcmp(g->algorithm, "BFS")){
        g->border = deque_construct();
        g->border_push = deque_push_back;
        g->border_pop = deque_pop_front;
        g->border_size = deque_size;
        g->border_destroy = deque_destroy;
    }
    if(!strcmp(g->algorithm, "UCS")){
        g->border = heap_constructor(city_cmp);
        g->border_push = heap_push;
        g->border_pop = heap_pop;
        g->border_size = heap_size;
        g->border_destroy = heap_destroy;
    }
    
    return g;
}

void graph_data(Graph * g){

    City * city_origin = vector_get(g->cities, g->start);

    g->border_push(g->border, city_origin);

    City * city_selected;
    int size = 1;

    while(size != 0){

        city_selected = (City *)g->border_pop(g->border);

        if(city_idx(city_selected) == g->end){
            g->num_cities_visited++;
            break;
        }

        if(!city_viseted(city_selected)){

            for (int i = 0; i < city_num_neighbors(city_selected); i++){
                
                Neighbor * n = city_get_neighbor(city_selected, i);
                City * city_neighbor = vector_get(g->cities, neighbor_idx(n));

                if(!strcmp(g->algorithm, "UCS") && city_get_in_border(city_neighbor)){

                    float dist_to_origin_before = city_get_dist_to_origin(city_neighbor);
                    float dist_to_origin_after = city_get_dist_to_origin(city_selected) + neighbor_distance(n);

                    if(dist_to_origin_after < dist_to_origin_before){
                        city_set_dad(city_neighbor, city_idx(city_selected));
                        city_set_dist_to_origin(city_neighbor, dist_to_origin_after);
                        g->border_push(g->border, city_neighbor);
                    }
                }

                else if(!city_viseted(city_neighbor) && !city_get_in_border(city_neighbor)){
                    city_set_dad(city_neighbor, city_idx(city_selected));
                    city_set_dist_to_origin(city_neighbor, (city_get_dist_to_origin(city_selected) + neighbor_distance(n)));
                    city_set_in_border(city_neighbor);
                    g->border_push(g->border, city_neighbor);
                }
            }

            city_set_viseted(city_selected);
            city_reset_in_border(city_selected);
            g->num_cities_visited++;
        }

        size = g->border_size(g->border);

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

    g->border_destroy(g->border);

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