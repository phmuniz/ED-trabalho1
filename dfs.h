#ifndef _DFS_H
#define _DFS_H

typedef struct Dfs Dfs;

typedef int (*destroy_fn)(void * item);

Dfs *dfs_construct();
void dfs_push(void *d, void * item);
void dfs_pop(void *d, destroy_fn destroy);
void dfs_destroy(void *d);

#endif