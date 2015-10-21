#pragma once
#include <stdint.h>

#if defined(_WIN32)
	#define GLFW_EXPOSE_NATIVE_WIN32
	#define GLFW_EXPOSE_NATIVE_WGL
#elif defined(__linux__)
	#define GLFW_EXPOSE_NATIVE_X11
	#define GLFW_EXPOSE_NATIVE_GLX
#else
	#error Your OS is not supported.
#endif

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include "funcload.h"
#include <CL/cl.h>
#include <CL/cl_gl.h>
#include "error_cl.h"
#include "kernels.src.h"
#include "world.h"

typedef struct{
	struct{
		uint32_t dim[2];
		GLFWwindow * window;
		uint32_t VAO;
		uint32_t VBO;
		uint32_t texture;
		uint32_t program;
	} gl;
	
	struct{
		uint32_t dim[2];
		cl_platform_id platform;
		cl_device_id device;
		cl_context context;
		cl_command_queue queue;
		cl_program program;
		cl_mem texture;
		cl_kernel kernel_core;
		
		cl_mem world_tree;
		cl_mem world_voxels;
	} cl;

	World world;
	
} Engine;

extern Engine engine;

void engine_init( uint32_t dim_cl[2], uint32_t dim_gl[2] );
void engine_destroy( void );
int engine_main( void );
