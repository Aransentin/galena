#include "render.h"
#include "engine.h"
#include "camera.h"
#include <math.h>

#include "otree.h"

static void render_cl( void )
{
	cl_int err;
	size_t worksize[2] = { engine.cl.dim[0], engine.cl.dim[1] };
	
	double rt = glfwGetTime()*3.1415926*0.25;
	int ww, wh;
	glfwGetWindowSize( engine.gl.window, &ww, &wh );
	
	Camera camera = {
		.pos = { 8.1, 8.1, 4.3 },
		.trg = { cos(rt)*2.0, sin(rt)*2.0, 0.0 },
		.nor = { 0.0, 0.0, 1.0 },
		.aspect = ww/(double)wh,
		.lens = 1.0,
	};
	camera_lookat( &camera );
	camera_normal_fix( &camera );
	camera_cl_update( &camera );
	err = clSetKernelArg( engine.cl.kernel_core, 1, sizeof( camera.cl ), &camera.cl );
	CLFCHECK( err );
	
	//TEST: set world data
	static int test = 0;
	if( !test )
	{
		OTnode_cl branches[6] = {
			{ .p = 1 },
			{ .p = 2 },
			{ .p = 3 },
			{ .p = 4 },
			{ .p = 5 },
			{ .p = 0 }
		};
		branches[0].bf = 1;
		branches[1].bf = 1;
		branches[2].bf = 1;
		branches[3].bf = 1;
		branches[4].bf = 1;
		branches[5].bf = 1;
		
		engine.cl.world_tree = clCreateBuffer( engine.cl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(branches), branches, &err );
		CLFCHECK( err );
		err = clSetKernelArg( engine.cl.kernel_core, 2, sizeof( cl_mem ), &engine.cl.world_tree );
		CLFCHECK( err );
		
		test = 1;
	}
	
	cl_event * evptr = NULL;
	#ifdef DEBUG
	cl_event ev;
	evptr = &ev;
	#endif
	
	/* Acquire OpenGL texture & call the core kernel */
	err = clEnqueueAcquireGLObjects( engine.cl.queue, 1, &engine.cl.texture, 0, NULL, NULL );
	CLFCHECK( err );
	err = clEnqueueNDRangeKernel( engine.cl.queue, engine.cl.kernel_core, 2, NULL, worksize, NULL, 0, NULL, evptr );
	CLFCHECK( err );
	err = clEnqueueReleaseGLObjects( engine.cl.queue, 1, &engine.cl.texture, 0, NULL, NULL );
	CLFCHECK( err );
	
	#ifdef DEBUG
	clWaitForEvents( 1 , &ev );
	cl_ulong ts_start, ts_end;
	static uint32_t counter = 0;
	static double ttime = 0.0;
	clGetEventProfilingInfo( ev, CL_PROFILING_COMMAND_START, sizeof(ts_start), &ts_start, NULL );
	clGetEventProfilingInfo( ev, CL_PROFILING_COMMAND_END, sizeof(ts_end), &ts_end, NULL );
	counter++;
	ttime += (double)(ts_end - ts_start);
	if( (counter & 31u) == 0 )
	{
		double ms = (ttime/counter)/1000000.0;
		printf( "Kernel execution time: %.2fms (%.0f fps)\n", ms, 1000.0/ms );
	}
	#endif
	
	clFinish( engine.cl.queue );
}

static void render_gl( void )
{
	//assumes all the stuff is still bound from the init
	glDrawArrays( GL_TRIANGLES, 0, 6 );
	glfwSwapBuffers( engine.gl.window );
}

void render_main( void )
{
	render_cl();
	render_gl();
}
