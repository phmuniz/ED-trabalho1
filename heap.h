
#ifndef _HEAP_H_
#define _HEAP_H_

typedef struct Heap Heap;

Heap *heap_constructor(int (*cmp_fn)(const void *, const void *));
void heap_push(void * h, void *data);
int heap_size(void * h);
void *heap_pop(void * h);
void heap_destroy(void * h);
void * heap_get(void * h, int i);

#endif