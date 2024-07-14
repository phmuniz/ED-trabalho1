#ifndef _DFS_H
#define _DFS_H

typedef struct Dfs Dfs;


Dfs *dfs_construct();
void dfs_push(void *d, void * item);
void *dfs_pop(void *d);
int dfs_size(void *d);
void dfs_destroy(void *d);

#endif