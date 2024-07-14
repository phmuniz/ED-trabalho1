#ifndef _CITY_H_
#define _CITY_H_

#include "vector.h"
#include <stdio.h>

typedef struct City City;

City * city_construct(FILE * file);

void city_destroy(City * c);

void city_print(City * c);

#endif