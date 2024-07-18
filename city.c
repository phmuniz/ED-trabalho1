#include "city.h"
#include "neighbor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct City
{
    int idx;
    char name[30];
    float x;
    float y;
    Vector * neighbors;
    int visited;
    int in_border;
    int dad_city;
    float dist_to_origin;
    float dist_to_destination;
};

City * city_construct(FILE * file, int idx){

    City * c = (City*)calloc(1, sizeof(City));

    c->neighbors = vector_construct();

    int num_neighbors = 0;

    c->idx = idx;

    fscanf(file, "%s %f %f %d", c->name, &c->x, &c->y, &num_neighbors);

    for (int j = 0; j < num_neighbors; j++)
    {
        Neighbor * n = neighbor_construct(file);
        vector_push_back(c->neighbors, n);
    }

    return c;
}

float city_get_dist_to_origin(City * c){
    return c->dist_to_origin;
}

void city_set_dist_to_origin(City * c, float dist){
    c->dist_to_origin = dist;
}

float city_get_dist_to_destination(City * c){
    return c->dist_to_destination;
}

void city_set_dist_to_destination(City * c, City * dest){

    float a = pow((dest->x - c->x), 2);
    float b = pow((dest->y - c->y), 2);

    c->dist_to_destination = sqrt(a+b);
}

int city_get_in_border(City * c){
    return c->in_border;
}

void city_set_in_border(City * c){
    c->in_border = 1;
}

void city_reset_in_border(City * c){
    c->in_border = 0;
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
    printf("DIST_TO_ORIGIN_CITY: %.2f\n", c->dist_to_origin);
    printf("DAD_CITY: %d\n", c->dad_city);
    printf("POSITION_CITY: %.2f %.2f\n\n", c->x, c->y);

    for (int i = 0; i < vector_size(c->neighbors); i++)
    {
        printf("NEIGHBOR %d\n", i);
        neighbor_print(vector_get(c->neighbors, i));
        printf("\n");
    }
}

int city_cmp(const void *a, const void *b)
{
    City *city_a = (City *)a;
    City *city_b = (City *)b;

    if (city_a->dist_to_origin < city_b->dist_to_origin)
        return 1;
    if (city_a->dist_to_origin > city_b->dist_to_origin)
        return -1;

    return 0;
}

int city_cmp_astar(const void *a, const void *b){

    City *city_a = (City *)a;
    City *city_b = (City *)b;

    if ((city_a->dist_to_origin + city_a->dist_to_destination) < (city_b->dist_to_origin + city_b->dist_to_destination))
        return 1;
    if ((city_a->dist_to_origin + city_a->dist_to_destination) > (city_b->dist_to_origin + city_b->dist_to_destination))
        return -1;

    return 0;
}