#include "vector.h"
#include "stdio.h"
#include "stdlib.h"

struct Vector{
    data_type *data;
    int size;
    int allocated;
};

Vector *vector_construct(){

    Vector * v = (Vector*)calloc(1, sizeof(Vector));

    v->allocated = 10;

    v->data = (data_type*)calloc(v->allocated, sizeof(data_type));

    return v;
}

void vector_destroy(Vector *v){

    free(v->data);
    free(v);
}

void vector_push_back(Vector *v, data_type val){

    if(v->size >= v->allocated){
        v->allocated *= 2;
        v->data = realloc(v->data, v->allocated * sizeof(data_type));
    }

    v->data[v->size] = val;
    v->size++;
}

int vector_size(Vector *v){
    return v->size;
}

data_type vector_get(Vector *v, int i){

    if(i < 0 || i >= v->size){
        printf("ERROR");
        exit(1);
    }

    return v->data[i];
}

void vector_set(Vector *v, int i, data_type val){

    if(i < 0 || i >= v->size){
        printf("ERROR");
        exit(1);
    }

    v->data[i] = val;
}

int vector_find(Vector *v, data_type val){

    for (int i = 0; i < v->size; i++)
    {
        if(v->data[i] == val) return i;
    }

    return -1;    
}

data_type vector_max(Vector *v, func_ptr_compare cmp){
    data_type maior = v->data[0];

    for (int i = 1; i < v->size; i++)
    {
        if(cmp(v->data[i], maior) > 0){
            maior = v->data[i];
        }
    }
    
    return maior;
}

data_type vector_min(Vector *v, func_ptr_compare cmp){
    data_type menor = v->data[0];

    for (int i = 1; i < v->size; i++)
    {
        if(cmp(v->data[i], menor) < 0){
            menor = v->data[i];
        }
    }
    
    return menor;
}

int vector_argmax(Vector *v, func_ptr_compare cmp){
    data_type maior = v->data[0];
    int indice = 0;

    for (int i = 1; i < v->size; i++)
    {
        if(cmp(v->data[i], maior) > 0){
            maior = v->data[i];
            indice = i;
        }
    }
    
    return indice;
}

int vector_argmin(Vector *v, func_ptr_compare cmp){
    data_type menor = v->data[0];
    int indice = 0;

    for (int i = 1; i < v->size; i++)
    {
        if(cmp(v->data[i], menor) < 0){
            menor = v->data[i];
            indice = i;
        }
    }
    
    return indice;
}

data_type vector_remove(Vector *v, int i){

    data_type val = v->data[i];

    for (int j = i; j < (v->size - 1); j++)
    {
        v->data[j] = v->data[j+1];
    }

    v->size--;
    
    return val;
}

data_type vector_pop_front(Vector *v){

    return vector_remove(v, 0);
}

data_type vector_pop_back(Vector *v){
    return vector_remove(v, v->size - 1);
}

void vector_insert(Vector *v, int i, data_type val){

    if(v->size >= v->allocated){
        v->allocated *= 2;
        v->data = realloc(v->data, v->allocated * sizeof(data_type));
    }

    for (int j = (v->size - 1); j >= i; j--)
    {
        v->data[j+1] = v->data[j];
    }

    v->data[i] = val;
    v->size++;
}

void vector_swap(Vector *v, int i, int j){

    data_type aux;

    aux = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = aux;
}

void vector_sort(Vector *v, func_ptr_compare cmp){

    int num_swaps;
    int j = 0;

    while(1){

        num_swaps = 0;

        for (int i = 0; i < (v->size - j - 1); i++){
            
            if(cmp(v->data[i], v->data[i+1]) > 0){
                vector_swap(v, i, i+1);
                num_swaps++;
            }
        }

        j++;

        if(!num_swaps) break;
        
    }
}

int vector_binary_search(Vector *v, data_type val, func_ptr_compare cmp){

    int i = 0, j = v->size - 1, center, val_found = 0;

    while(1){

        center = ((j - i) / 2) + i;

        if(cmp(val, v->data[center]) > 0){
            i = center + 1;
        }

        else if(cmp(val, v->data[center]) < 0){
            j = center - 1;
        }

        else{
            val_found = 1;
            break;
        }

        if(i > j) break;
    }

    if(val_found) return center;
    else return -1;
}

void vector_reverse(Vector *v){

    int i = 0, j= v->size - 1;

    while(i < j){
        
        vector_swap(v, i, j);

        i++;
        j--;
    }
}