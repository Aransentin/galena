#include "world.h"

void world_init( World *world )
{
    *world = ( World ){.dirty = 1};
    octree_init( &world->tree );
}

void world_destroy( World *world ) { octree_destroy( &world->tree ); }
