#include <stdlib.h>
#include "engine.h"
#include "render.h"

int main( void )
{
    uint32_t dim_cl[2] = {1024, 512};
    uint32_t dim_gl[2] = {1024, 512};
    engine_init( dim_cl, dim_gl );
    world_init( &engine.world );

    while ( 1 )
    {
        if ( engine_main() < 0 )
            break;

        render_main();
    }

    engine_destroy();
    return EXIT_SUCCESS;
}
