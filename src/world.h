#pragma once
#include "octree.h"
#include <stdint.h>

typedef struct
{
    Octree tree;
    uint8_t dirty;
} World;

void world_init( World *world );
void world_destroy( World *world );
