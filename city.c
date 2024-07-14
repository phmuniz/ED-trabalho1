#include "city.h"
#include "neighbor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct City
{
    int idx;
    char name[30];
    int x;
    int y;
    Vector * neighbors;
    int visited;
    int dad_city;
    int dist_to_origin;
};

City * city_construct(FILE * file){

    City * c = (City*)calloc(1, sizeof(City));

    c->neighbors = vector_construct();

    int num_neighbors;

    fscanf(file, "%d %s %d %d %d", &c->idx, c->name, &c->x, &c->y, &num_neighbors);

    for (int j = 0; j < num_neighbors; j++)
    {
        Neighbor * n = neighbor_construct(file);
        vector_push_back(c->neighbors, n);
    }

    return c;
}

char * city_name(City * c){
    return c->name;
}

int city_idx(City * c){
    return c->idx;
}

int city_viseted(City * c){
    return c->visited;
}

void city_set_viseted(City * c){
    c->visited = 1;
}

int city_num_neighbors(City * c){
    return vector_size(c->neighbors);
}

int city_get_dad(City * c){
    return c->dad_city;
}

void city_set_dad(City * c, int idx){
    c->dad_city = idx;
}

Neighbor * city_get_neighbor(City * c, int idx){
    return vector_get(c->neighbors, idx);
}

void city_destroy(City * c){

    for (int i = 0; i < vector_size(c->neighbors); i++)
    {
        Neighbor * n = vector_get(c->neighbors, i);
        neighbor_destroy(n);
    }

    vector_destroy(c->neighbors);

    free(c);
}

void city_print(City * c){

    printf("IDX_CITY: %d\n", c->idx);
    printf("NAME_CITY: %s\n", c->name);
    printf("VISITED_CITY: %d\n", c->visited);
    printf("DIST_TO_ORIGIN_CITY: %d\n", c->dist_to_origin);
    printf("DAD_CITY: %d\n", c->dad_city);
    printf("POSITION_CITY: %d %d\n\n", c->x, c->y);

    for (int i = 0; i < vector_size(c->neighbors); i++)
    {
        printf("NEIGHBOR %d\n", i);
        neighbor_print(vector_get(c->neighbors, i));
        printf("\n");
    }
}