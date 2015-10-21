#include "octree.h"

void octree_init( Octree * tree )
{
	*tree = (Octree){ .nodes={.n=0} };
	vector_init( tree->nodes );
	vector_init( tree->leaves );
	
	Octnode root = { .p={0} };
	vector_push( tree->nodes, root );
}

void octree_destroy( Octree * tree )
{
	vector_destroy( tree->nodes );
	vector_destroy( tree->leaves );
}

static inline uint32_t octree_node_new( Octree * tree )
{
	Octnode node = { .p={0} };
	vector_push( tree->nodes, node );
	return tree->nodes.n-1;
}

static inline uint32_t octree_leaf_new( Octree * tree )
{
	Octleaf leaf = { .rgba={0} };
	vector_push( tree->leaves, leaf );
	return tree->leaves.n-1;
}

const Octleaf * octleaf_cget( const Octree * tree, uint32_t x, uint32_t y, uint32_t z )
{
	const Octnode * cnode = &tree->nodes.data[0];
	for( uint32_t i=0; i<WDEPTH-1; i++ )
	{
		int obit = 0;
		obit += 1*(( x >> (WDEPTH-i-1) ) & 1);
		obit += 2*(( y >> (WDEPTH-i-1) ) & 1);
		obit += 4*(( z >> (WDEPTH-i-1) ) & 1);
		
		if( cnode->p[obit] == 0 )
			return NULL;
		else
			cnode = tree->nodes.data + cnode->p[obit];
	}
	
	int obit = 0;
	obit += 1*( x & 1 );
	obit += 2*( y & 1 );
	obit += 4*( z & 1 );
	if( cnode->p[obit] == 0 )
		return NULL;
	else
		return tree->leaves.data + cnode->p[obit];
}

Octleaf * octleaf_get( Octree * tree, uint32_t x, uint32_t y, uint32_t z )
{
	vector_alloc_limit( tree->nodes, 32 );
	
	Octnode * cnode = &tree->nodes.data[0];
	for( uint32_t i=0; i<WDEPTH-1; i++ )
	{
		int obit = 0;
		obit += 1*(( x >> (WDEPTH-i-1) ) & 1);
		obit += 2*(( y >> (WDEPTH-i-1) ) & 1);
		obit += 4*(( z >> (WDEPTH-i-1) ) & 1);
		
		if( cnode->p[obit] == 0 )
		{
			uint32_t nn = octree_node_new( tree );
			cnode->p[obit] = nn;
			tree->nodes.data[nn].parent = (uint32_t)(cnode - tree->nodes.data);
			cnode = tree->nodes.data + nn;
		}
		else
		{
			cnode = tree->nodes.data + cnode->p[obit];
		}
	}
	
	int obit = 0;
	obit += 1*( x & 1 );
	obit += 2*( y & 1 );
	obit += 4*( z & 1 );
	if( cnode->p[obit] == 0 )
	{
		uint32_t nl = octree_leaf_new( tree );
		cnode->p[obit] = nl;
		return tree->leaves.data + nl;
	}
	else
	{
		return tree->leaves.data + cnode->p[obit];
	}
}







