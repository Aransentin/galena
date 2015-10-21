#include "init.h"
#include "engine.h"
#include "xplat.h"
#include "shader.h"
#include <string.h>

void init_cl_pre( void )
{
	/* Load the core OpenCL stuff. We do it before anything else, so that if it's not supported we'll fail early.*/
	cl_int err;
	cl_uint pcnt;
	err = clGetPlatformIDs( 1, &engine.cl.platform, &pcnt );
	CLFCHECK( err );
	if( pcnt == 0 )
		xplat_error( "No OpenCL platform found." );

	cl_uint dcnt;
	err = clGetDeviceIDs( engine.cl.platform, CL_DEVICE_TYPE_DEFAULT, 1, &engine.cl.device, &dcnt );
	CLFCHECK( err );
	if( dcnt == 0 )
		xplat_error( "No OpenCL device found." );
	
    #if !defined( NOSHARING )
	char extstr[2048] = { 0 };
	err = clGetDeviceInfo( engine.cl.device, CL_DEVICE_EXTENSIONS, 2048, extstr, NULL );
	CLFCHECK( err );
	if ( !strstr( extstr, "cl_khr_gl_sharing") )
		xplat_error( "Compiled for the OpenCL \"cl_khr_gl_sharing\" extension, but it's not supported by the device." );
    #endif
}

static void opencl_debug_callback( const char * errinfo, const void * private_info, size_t cb, void * user_data )
{
	(void)private_info;
	(void)cb;
	(void)user_data;
	printf( "OpenCL debug message: %s\n", errinfo );
}

void init_cl_post( void )
{
	cl_int err;
	cl_context_properties context_properties[] = 
	{
		CL_CONTEXT_PLATFORM, (cl_context_properties)engine.cl.platform,
        #if !defined( NOSHARING )
            #if defined(__linux__)
            CL_GL_CONTEXT_KHR, (cl_context_properties)(glfwGetGLXContext( engine.gl.window )),
            CL_GLX_DISPLAY_KHR, (cl_context_properties)(glfwGetX11Display()),
            #elif defined(_WIN32)
            CL_GL_CONTEXT_KHR, (cl_context_properties)(glfwGetWGLContext( engine.gl.window )),
            CL_WGL_HDC_KHR, (cl_context_properties)(GetDC(glfwGetWin32Window( engine.gl.window ))),
            #endif
        #endif
		0, 0,
	};
	
	void (*callback)(const char *, const void *, size_t, void *) = NULL;
	#if defined( DEBUG )
	callback = opencl_debug_callback;
	#endif
	
	engine.cl.context = clCreateContext( context_properties, 1, &engine.cl.device, callback, NULL, &err );
	CLFCHECK( err );
	
	cl_command_queue_properties cqprop = 0;
	#if defined( DEBUG )
	cqprop = CL_QUEUE_PROFILING_ENABLE;
	#endif
	
	engine.cl.queue = clCreateCommandQueue( engine.cl.context, engine.cl.device, cqprop, &err );
	CLFCHECK( err );
	
    #if defined( NOSHARING )
    const cl_image_format format = {
        .image_channel_order = CL_RGBA,
        .image_channel_data_type = CL_UNORM_INT8,
    };
    engine.cl.texture = clCreateImage2D( engine.cl.context, CL_MEM_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR, &format, engine.cl.dim[0], engine.cl.dim[1], 0, NULL, &err );
    CLFCHECK( err );
    #else
	engine.cl.texture = clCreateFromGLTexture2D( engine.cl.context, CL_MEM_WRITE_ONLY, GL_TEXTURE_2D, 0, engine.gl.texture, &err );
	CLFCHECK( err );
    #endif
    
	const char * ksrc = kernel_src_str;
	engine.cl.program = clCreateProgramWithSource( engine.cl.context, 1, &ksrc, NULL, &err );
	CLFCHECK( err );
	
	char opt[256] = {0};
	//Some extra optimizations, for testing: -cl-single-precision-constant -cl-denorms-are-zero -cl-strict-aliasing -cl-fast-relaxed-math 
	snprintf( opt, 256, "-D DIM_X=%du -D DIM_Y=%du -D WDEPTH=%du -D WDIM=%du -Werror", engine.cl.dim[0], engine.cl.dim[1], WDEPTH, WDIM );
	err = clBuildProgram( engine.cl.program, 1, &engine.cl.device, opt, NULL, NULL );
	if( err )
	{
		char buf[1024*4] = { 0 };
		clGetProgramBuildInfo( engine.cl.program, engine.cl.device, CL_PROGRAM_BUILD_LOG, 1024*4, buf, NULL );
		printf( "OpenCL kernel compile error:\n%s\n", buf );
		CLFCHECK( err );
	}
	
	engine.cl.kernel_core = clCreateKernel( engine.cl.program, "core", &err );
	CLFCHECK( err );
	
	err = clSetKernelArg( engine.cl.kernel_core, 0, sizeof( cl_mem ), &engine.cl.texture );
	CLFCHECK( err );
}

static void glfw_resize_callback( GLFWwindow * window, int w, int h )
{
	(void)window;
	glViewport( 0, 0, w, h );
}

void init_gl( void )
{
	if( glfwInit() != GL_TRUE )
		xplat_error(  "Failed to initialize GLFW." );
	
	/* No deprecated crap, please */
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	engine.gl.window = glfwCreateWindow( (int)engine.gl.dim[0], (int)engine.gl.dim[1], "Galena", NULL, NULL );
	
	glfwMakeContextCurrent( engine.gl.window );
	funcload_load();
	
	glfwSetWindowSizeCallback( engine.gl.window, glfw_resize_callback );
	glfwSwapInterval( 1 );
	
	/* Might be enabled for motion blur later */
	// glEnable( GL_BLEND );
	// glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	
	glGenVertexArrays( 1, &engine.gl.VAO );
	glGenBuffers( 1, &engine.gl.VBO );
	float vdata[2*6] = 
	{
		-1.0f, -1.0f, 1.0f, -1.0f, 1.0f,  1.0f,
		-1.0f, -1.0f, 1.0f,  1.0f, -1.0f,  1.0f,
	};
	
	glBindVertexArray( engine.gl.VAO );
	glBindBuffer( GL_ARRAY_BUFFER, engine.gl.VBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof(vdata), vdata, GL_STATIC_DRAW );
	glEnableVertexAttribArray( 0 );
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0 );
	
	glActiveTexture( GL_TEXTURE0 );
	glGenTextures( 1, &engine.gl.texture );
	glBindTexture( GL_TEXTURE_2D, engine.gl.texture );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, (int)engine.cl.dim[0], (int)engine.cl.dim[1], 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL );
	
	engine.gl.program = shader_load();
	
	//uint32_t err = glGetError();
	//printf( "GL error: %d\n", err );
}
