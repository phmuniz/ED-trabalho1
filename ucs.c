#include "ucs.h"
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ucs{
    Heap * h;
};

Ucs *ucs_construct(int (*cmp_fn)(const void *, const void *)){

    Ucs * u = (Ucs *)calloc(1, sizeof(Ucs));

    u->h = heap_constructor(cmp_fn);

    return u;
}
void ucs_push(void *u, void * item){

    Ucs * ucs = (Ucs*)u;

    heap_push(ucs->h, item);
}
void *ucs_pop(void *u){

    Ucs * ucs = (Ucs*)u;

    return heap_pop(ucs->h);
}
int ucs_size(void *u){

    Ucs * ucs = (Ucs*)u;

    return heap_size(ucs->h);
}
void ucs_destroy(void *u){

    Ucs * ucs = (Ucs*)u;

    heap_destroy(ucs->h);

    free(ucs);
}

void * ucs_get(void *u, int i){

    Ucs * ucs = (Ucs*)u;

    return heap_get(ucs->h, i);
}