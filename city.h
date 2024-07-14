#ifndef _CITY_H_
#define _CITY_H_

#include "vector.h"
#include "neighbor.h"
#include <stdio.h>

typedef struct City City;

City * city_construct(FILE * file);

char * city_name(City * c);

int city_idx(City * c);

int city_viseted(City * c);

void city_set_viseted(City * c);

int city_num_neighbors(City * c);

int city_get_dad(City * c);

void city_set_dad(City * c, int idx);

Neighbor * city_get_neighbor(City * c, int idx);

void city_destroy(City * c);

void city_print(City * c);

#endif