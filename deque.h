
#ifndef _DEQUE_H_
#define _DEQUE_H_

typedef struct Deque Deque;

Deque *deque_construct();
void deque_push_back(void * d, void * item);
void deque_push_front(void * d, void * item);
void * deque_pop_back(void * d);
void * deque_pop_front(void * d);
int deque_size(void * d);
void deque_destroy(void * d);

#endif