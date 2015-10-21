#include "engine.h"
#include "init.h"
Engine engine;

void engine_init( uint32_t dim_cl[2], uint32_t dim_gl[2] )
{
	engine = (Engine){
		.gl.dim = { dim_gl[0], dim_gl[1] },
		.cl.dim = { dim_cl[0], dim_cl[1] },
	};

	init_cl_pre();
	init_gl();
	init_cl_post();
}

int engine_main( void )
{
	glfwPollEvents();
	if( glfwWindowShouldClose( engine.gl.window ) )
		return -1;
	return 0;
}

void engine_destroy( void )
{
	
}
