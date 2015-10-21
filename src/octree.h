#pragma once
#define WDEPTH 8
#define WDIM 256

#include <stdint.h>
#include "vector.h"

typedef struct
{
	uint8_t rgba[4];
} Octleaf;

typedef struct
{
	uint32_t parent;
	uint32_t p[8];
} Octnode;

typedef struct
{
	vector( Octnode ) nodes;
	vector( Octleaf ) leaves;
} Octree;

void octree_init( Octree * tree );
void octree_destroy( Octree * tree );

const Octleaf * octleaf_cget( const Octree * tree, uint32_t x, uint32_t y, uint32_t z );
Octleaf * octleaf_get( Octree * tree, uint32_t x, uint32_t y, uint32_t z );
