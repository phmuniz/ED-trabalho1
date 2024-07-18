#ifndef _BFS_H
#define _BFS_H

typedef struct Bfs Bfs;


Bfs *bfs_construct();
void bfs_push(void *b, void * item);
void *bfs_pop(void *b);
int bfs_size(void *b);
void bfs_destroy(void *b);

#endif