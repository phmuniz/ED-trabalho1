#ifndef _UCS_H
#define _UCS_H

typedef struct Ucs Ucs;


Ucs *ucs_construct(int (*cmp_fn)(const void *, const void *));
void ucs_push(void *u, void * item);
void *ucs_pop(void *u);
int ucs_size(void *u);
void ucs_destroy(void *u);
void * ucs_get(void *u, int i);

#endif