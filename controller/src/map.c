#include "map.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define DEFAULT_CHUNK_WIDTH 500
#define DEFAULT_CHUNK_HEIGHT 500

int map_init(Map* map)
{
    int err;
    
    map->chunk_width = DEFAULT_CHUNK_WIDTH;
    map->chunk_height = DEFAULT_CHUNK_HEIGHT;
    err = ct_init(&map->tree);
    if (err)
    {
        return err;
    }

    return 0;
}

int map_open(Map* map)
{
    return 0;
}

int map_save(Map* map)
{
    return 0;
}

int map_free(Map* map)
{
    return 0;
}

int ct_init(ChunkTree* ct)
{
    int err;

    ct->root = malloc(sizeof(CTNode));
    if (ct->root == NULL)
    {
        return 1;
    }

    err = ctnode_init(ct->root, DEFAULT_CHUNK_WIDTH, DEFAULT_CHUNK_HEIGHT);
    if (err)
    {
        return 1;
    }

    return 0;
}

int ct_free(ChunkTree* ct)
{
    return 0;
}

int ctnode_init(CTNode* node, uint32_t w, uint32_t h)
{
    //node->width = w;
    //node->height = h;
    //node->grid = malloc(w * h * sizeof(uint32_t));
    /*if (node->grid == NULL)
    {
        return 1;
    }*/

    return 0;
}

int ctnode_free(CTNode* node)
{
    return 0;
}
