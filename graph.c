#include "graph.h"
#include "city.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Graph
{
    char algorithm[5];
    int start;
    int end;
    Vector * cities;
    Vector * visited;
    void * border;
};