#ifndef _CITY_H_
#define _CITY_H_

#include "vector.h"
#include "neighbor.h"
#include <stdio.h>

typedef struct City City;

City * city_construct(FILE * file, int idx);

char * city_name(City * c);

int city_idx(City * c);

int city_viseted(City * c);

void city_set_viseted(City * c);

int city_num_neighbors(City * c);

int city_get_dad(City * c);

void city_set_dad(City * c, int idx);

float city_get_dist_to_origin(City * c);

void city_set_dist_to_origin(City * c, float dist);

float city_get_dist_to_destination(City * c);

void city_set_dist_to_destination(City * c, City * dest);

int city_get_in_border(City * c);

void city_set_in_border(City * c);

void city_reset_in_border(City * c);

Neighbor * city_get_neighbor(City * c, int idx);

void city_destroy(City * c);

void city_print(City * c);

int city_cmp(const void *a, const void *b);

int city_cmp_astar(const void *a, const void *b);

#endif