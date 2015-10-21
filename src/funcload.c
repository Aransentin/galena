#include "funcload.h"
#include "xplat.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

PFNGLVIEWPORTPROC glViewport_fun;
PFNGLENABLEPROC glEnable_fun;
PFNGLBLENDFUNCPROC glBlendFunc_fun;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays_fun;
PFNGLBUFFERDATAPROC glBufferData_fun;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer_fun;
PFNGLGENBUFFERSPROC glGenBuffers_fun;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray_fun;
PFNGLBINDBUFFERPROC glBindBuffer_fun;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray_fun;
PFNGLACTIVETEXTUREPROC glActiveTexture_fun;
PFNGLGENTEXTURESPROC glGenTextures_fun;
PFNGLBINDTEXTUREPROC glBindTexture_fun;
PFNGLTEXPARAMETERIPROC glTexParameteri_fun;
PFNGLTEXIMAGE2DPROC glTexImage2D_fun;
PFNGLGETERRORPROC glGetError_fun;
PFNGLUSEPROGRAMPROC glUseProgram_fun;
PFNGLCREATEPROGRAMPROC glCreateProgram_fun;
PFNGLUNIFORM1IPROC glUniform1i_fun;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation_fun;
PFNGLATTACHSHADERPROC glAttachShader_fun;
PFNGLLINKPROGRAMPROC glLinkProgram_fun;
PFNGLDELETESHADERPROC glDeleteShader_fun;
PFNGLDETACHSHADERPROC glDetachShader_fun;
PFNGLCREATESHADERPROC glCreateShader_fun;
PFNGLSHADERSOURCEPROC glShaderSource_fun;
PFNGLCOMPILESHADERPROC glCompileShader_fun;
PFNGLGETSHADERIVPROC glGetShaderiv_fun;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog_fun;
PFNGLDRAWARRAYSPROC glDrawArrays_fun;

static inline void funcload_test( void (*ptr)(void) )
{
	if( ptr == NULL )
		xplat_error( "Error loading the OpenGL function pointers." );
}

void funcload_load( void )
{
	funcload_test((void(*)())( glViewport_fun =	(PFNGLVIEWPORTPROC)glfwGetProcAddress( "glViewport" )) );
	funcload_test((void(*)())( glEnable_fun	= (PFNGLENABLEPROC)glfwGetProcAddress( "glEnable" )) );
	funcload_test((void(*)())( glBlendFunc_fun = (PFNGLBLENDFUNCPROC)glfwGetProcAddress( "glBlendFunc" )) );
	funcload_test((void(*)())( glGenVertexArrays_fun = (PFNGLGENVERTEXARRAYSPROC)glfwGetProcAddress( "glGenVertexArrays" )) );
	funcload_test((void(*)())( glBufferData_fun = (PFNGLBUFFERDATAPROC)glfwGetProcAddress( "glBufferData" )) );
	funcload_test((void(*)())( glVertexAttribPointer_fun = (PFNGLVERTEXATTRIBPOINTERPROC)glfwGetProcAddress( "glVertexAttribPointer" )) );
	funcload_test((void(*)())( glGenBuffers_fun = (PFNGLGENBUFFERSPROC)glfwGetProcAddress( "glGenBuffers" )) );
	funcload_test((void(*)())( glBindVertexArray_fun = (PFNGLBINDVERTEXARRAYPROC)glfwGetProcAddress( "glBindVertexArray" )) );
	funcload_test((void(*)())( glBindBuffer_fun = (PFNGLBINDBUFFERPROC)glfwGetProcAddress( "glBindBuffer" )) );
	funcload_test((void(*)())( glEnableVertexAttribArray_fun = (PFNGLENABLEVERTEXATTRIBARRAYPROC)glfwGetProcAddress( "glEnableVertexAttribArray" )) );
	funcload_test((void(*)())( glActiveTexture_fun = (PFNGLACTIVETEXTUREPROC)glfwGetProcAddress( "glActiveTexture" )) );
	funcload_test((void(*)())( glGenTextures_fun = (PFNGLGENTEXTURESPROC)glfwGetProcAddress( "glGenTextures" )) );
	funcload_test((void(*)())( glBindTexture_fun = (PFNGLBINDTEXTUREPROC)glfwGetProcAddress( "glBindTexture" )) );
	funcload_test((void(*)())( glTexParameteri_fun = (PFNGLTEXPARAMETERIPROC)glfwGetProcAddress( "glTexParameteri" )) );
	funcload_test((void(*)())( glTexImage2D_fun = (PFNGLTEXIMAGE2DPROC)glfwGetProcAddress( "glTexImage2D" )) );
	funcload_test((void(*)())( glGetError_fun = (PFNGLGETERRORPROC)glfwGetProcAddress( "glGetError" )) );
	funcload_test((void(*)())( glUseProgram_fun = (PFNGLUSEPROGRAMPROC)glfwGetProcAddress( "glUseProgram" )) );
	funcload_test((void(*)())( glCreateProgram_fun = (PFNGLCREATEPROGRAMPROC)glfwGetProcAddress( "glCreateProgram" )) );
	funcload_test((void(*)())( glUniform1i_fun = (PFNGLUNIFORM1IPROC)glfwGetProcAddress( "glUniform1i" )) );
	funcload_test((void(*)())( glGetUniformLocation_fun = (PFNGLGETUNIFORMLOCATIONPROC)glfwGetProcAddress( "glGetUniformLocation" )) );
	funcload_test((void(*)())( glAttachShader_fun = (PFNGLATTACHSHADERPROC)glfwGetProcAddress( "glAttachShader" )) );
	funcload_test((void(*)())( glLinkProgram_fun = (PFNGLLINKPROGRAMPROC)glfwGetProcAddress( "glLinkProgram" )) );
	funcload_test((void(*)())( glDeleteShader_fun = (PFNGLDELETESHADERPROC)glfwGetProcAddress( "glDeleteShader" )) );
	funcload_test((void(*)())( glDetachShader_fun = (PFNGLDETACHSHADERPROC)glfwGetProcAddress( "glDetachShader" )) );
	funcload_test((void(*)())( glCreateShader_fun = (PFNGLCREATESHADERPROC)glfwGetProcAddress( "glCreateShader" )) );
	funcload_test((void(*)())( glShaderSource_fun = (PFNGLSHADERSOURCEPROC)glfwGetProcAddress( "glShaderSource" )) );
	funcload_test((void(*)())( glCompileShader_fun = (PFNGLCOMPILESHADERPROC)glfwGetProcAddress( "glCompileShader" )) );
	funcload_test((void(*)())( glGetShaderiv_fun = (PFNGLGETSHADERIVPROC)glfwGetProcAddress( "glGetShaderiv" )) );
	funcload_test((void(*)())( glGetShaderInfoLog_fun = (PFNGLGETSHADERINFOLOGPROC)glfwGetProcAddress( "glGetShaderInfoLog" )) );
	funcload_test((void(*)())( glDrawArrays_fun = (PFNGLDRAWARRAYSPROC)glfwGetProcAddress( "glDrawArrays" )) );
}
