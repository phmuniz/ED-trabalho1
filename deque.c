#include "deque.h"
#include <stdio.h>
#include <stdlib.h>

struct Deque{
    
    void **arr;
    int start;
    int end;
    int size;
    int allocated;    
};

void deque_realloc(Deque *f){

    int alloc = f->allocated * 2;
    void **array = (void**)calloc(alloc, sizeof(void*));

    int j = f->start;
    for (int i = 0; i < f->size; i++){

        if(j == f->allocated){
            j = 0;
        }
        array[i] = f->arr[j];
        j++;
    }
    
    f->start = 0;
    f->end = f->size;
    f->allocated = alloc;
    
    free(f->arr);

    f->arr = array;
}

Deque *deque_construct(){

    Deque * f = (Deque*)calloc(1, sizeof(Deque));

    f->arr = (void**)calloc(10, sizeof(void*));
    f->start = 0;
    f->end = 0;
    f->size = 0;
    f->allocated = 3;

    return f;
}

void deque_push_back(Deque *f, void * item){

    if(f->size >= f->allocated){
        deque_realloc(f);
    }

    f->arr[f->end] = item;
    f->end = (f->end + 1) % f->allocated;
    f->size++;
}

void deque_push_front(Deque *f, void * item){

    if(f->size >= f->allocated){
        deque_realloc(f);
    }

    if(f->start == 0){
        f->start = f->allocated - 1;
    }
    else f->start--;

    f->arr[f->start] = item;
    f->size++;
}

void * deque_pop_back(Deque *f){

    if(f->end == 0){
        f->end = f->allocated - 1;
    }
    else f->end--;

    f->size--;
    return f->arr[f->end];
}

void * deque_pop_front(Deque *f){

    void * val = f->arr[f->start];
    f->start = (f->start + 1) % f->allocated;
    f->size--;
    return val;
}

void deque_destroy(Deque *f){
    free(f->arr);
    free(f);
}