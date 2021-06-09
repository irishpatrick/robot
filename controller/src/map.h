#ifndef MAP_H
#define MAP_H

#include <stdint.h>

typedef struct _Chunk
{
    uint32_t* grid;
    uint32_t width;
    uint32_t height;
} Chunk;

typedef struct _CTNode
{
    Chunk* chnk;
} CTNode;

typedef struct _ChunkTree
{
    CTNode* root;
} ChunkTree;

typedef struct _Map
{
    uint32_t chunk_width;
    uint32_t chunk_height;
    ChunkTree tree;
} Map;

int map_init(Map*);
int map_open(Map*);
int map_save(Map*);
int map_free(Map*);

int ct_init(ChunkTree*);
int ct_free(ChunkTree*);

int ctnode_init(CTNode*, uint32_t, uint32_t);
int ctnode_free(CTNode*);

#endif /* MAP_H */
