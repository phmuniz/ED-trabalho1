#include "city.h"
#include "neighbor.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct City
{
    int idx;
    char name[30];
    int x;
    int y;
    int num_neighbors;
    Vector * neighbors;
};
