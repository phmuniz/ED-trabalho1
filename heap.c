#include "heap.h"
#include "stdio.h"
#include "stdlib.h"
#include "vector.h"
#include <math.h>

struct Heap{
    
    Vector * data;
    int (*cmp_fn)(const void *, const void *);
};

Heap *heap_constructor(int (*cmp_fn)(const void *, const void *)){

    Heap * h = (Heap*)calloc(1, sizeof(Heap));

    h->data = vector_construct();

    h->cmp_fn = cmp_fn;

    return h;
}

void heap_push(void * h, void *data){

    Heap * heap = (Heap*)h;

    int idx_dad;

    vector_push_back(heap->data, data);

    int idx_data = vector_size(heap->data) - 1;

    while(1){

        idx_dad = floor((idx_data - 1)/2);

        if(idx_dad < 0) break;

        if(heap->cmp_fn(vector_get(heap->data, idx_data), vector_get(heap->data, idx_dad)) > 0){

            vector_swap(heap->data, idx_dad, idx_data);
            idx_data = idx_dad;
        }

        else break;
    }
}

int heap_size(void * h){
    Heap * heap = (Heap*)h;
    return vector_size(heap->data);
}

void *heap_pop(void * h){

    Heap * heap = (Heap*)h;

    vector_swap(heap->data, 0, vector_size(heap->data) - 1);

    void * value = vector_pop_back(heap->data);

    int idx_dad = 0, idx_child_left, idx_child_right;

    int size = vector_size(heap->data);

    while (1){
        
        idx_child_left = 2 * idx_dad + 1;
        idx_child_right = 2 * idx_dad + 2;
        int idx_largest = idx_dad;

        if(idx_child_left < size && 
        heap->cmp_fn(vector_get(heap->data, idx_child_left), vector_get(heap->data, idx_largest)) > 0){

            idx_largest = idx_child_left;
        }

        if(idx_child_right < size && 
        heap->cmp_fn(vector_get(heap->data, idx_child_right), vector_get(heap->data, idx_largest)) > 0){

            idx_largest = idx_child_right;
        }

        if(idx_dad != idx_largest){
            vector_swap(heap->data, idx_dad, idx_largest);
            idx_dad = idx_largest;
        }
        else break;
    }
    
    return value;
}

void heap_destroy(void * h){

    Heap * heap = (Heap*)h;

    vector_destroy(heap->data);
    free(heap);
}

void * heap_get(void * h, int i){

    Heap * heap = (Heap*)h;

    return vector_get(heap->data, i);
}