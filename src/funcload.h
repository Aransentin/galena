#pragma once
#include <stddef.h>
#include <stdint.h>
void funcload_load( void );

/* Yeah, I'm trashing all that GLint crap. */
#define GL_FALSE 0
#define GL_TRUE 1
#define GL_BLEND 0x0BE2
#define GL_SRC_ALPHA 0x0302
#define GL_ONE_MINUS_SRC_ALPHA 0x0303
#define GL_ARRAY_BUFFER 0x8892
#define GL_STATIC_DRAW 0x88E4
#define GL_FLOAT 0x1406
#define GL_TEXTURE0 0x84C0
#define GL_TEXTURE_2D 0x0DE1
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_NEAREST 0x2600
#define GL_LINEAR 0x2601
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_RGBA8 0x8058
#define GL_RGBA 0x1908
#define GL_UNSIGNED_BYTE 0x1401
#define GL_VERTEX_SHADER 0x8B31
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_COMPILE_STATUS 0x8B81

#define glViewport glViewport_fun
typedef void (* PFNGLVIEWPORTPROC)( int32_t x, int32_t y, int32_t width, int32_t height );
extern PFNGLVIEWPORTPROC glViewport_fun;

#define glEnable glEnable_fun
typedef void (* PFNGLENABLEPROC)( uint32_t cap );
extern PFNGLENABLEPROC glEnable_fun;

#define glBlendFunc glBlendFunc_fun
typedef void (* PFNGLBLENDFUNCPROC)( uint32_t sfactor, uint32_t dfactor );
extern PFNGLBLENDFUNCPROC glBlendFunc_fun;

#define glGenVertexArrays glGenVertexArrays_fun
typedef void (* PFNGLGENVERTEXARRAYSPROC)( int32_t n, uint32_t * arrays );
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays_fun;

#define glBufferData glBufferData_fun
typedef void (* PFNGLBUFFERDATAPROC)( uint32_t target, ptrdiff_t size, const void * data, uint32_t usage );
extern PFNGLBUFFERDATAPROC glBufferData_fun;

#define glVertexAttribPointer glVertexAttribPointer_fun
typedef void (* PFNGLVERTEXATTRIBPOINTERPROC)( uint32_t index, int32_t size, uint32_t type, unsigned char normalized, int32_t stride, const void * pointer );
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer_fun;

#define glGenBuffers glGenBuffers_fun
typedef void (* PFNGLGENBUFFERSPROC)( int32_t n, uint32_t * buffers );
extern PFNGLGENBUFFERSPROC glGenBuffers_fun;

#define glBindVertexArray glBindVertexArray_fun
typedef void (* PFNGLBINDVERTEXARRAYPROC)( uint32_t array );
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray_fun;

#define glBindBuffer glBindBuffer_fun
typedef void (* PFNGLBINDBUFFERPROC)( uint32_t target, uint32_t buffer );
extern PFNGLBINDBUFFERPROC glBindBuffer_fun;

#define glEnableVertexAttribArray glEnableVertexAttribArray_fun
typedef void (* PFNGLENABLEVERTEXATTRIBARRAYPROC)( uint32_t index );
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray_fun;

#define glActiveTexture glActiveTexture_fun
typedef void (* PFNGLACTIVETEXTUREPROC)( uint32_t texture );
extern PFNGLACTIVETEXTUREPROC glActiveTexture_fun;

#define glGenTextures glGenTextures_fun
typedef void (* PFNGLGENTEXTURESPROC)( int32_t n, uint32_t * textures );
extern PFNGLGENTEXTURESPROC glGenTextures_fun;

#define glBindTexture glBindTexture_fun
typedef void (* PFNGLBINDTEXTUREPROC)( uint32_t target, uint32_t texture );
extern PFNGLBINDTEXTUREPROC glBindTexture_fun;

#define glTexParameteri glTexParameteri_fun
typedef void (* PFNGLTEXPARAMETERIPROC)( uint32_t target, uint32_t pname, int32_t param );
extern PFNGLTEXPARAMETERIPROC glTexParameteri_fun;

#define glTexImage2D glTexImage2D_fun
typedef void (* PFNGLTEXIMAGE2DPROC)( uint32_t target, int32_t level, int32_t internalFormat, int32_t width, int32_t height, int32_t border, uint32_t format, uint32_t type, const void * data );
extern PFNGLTEXIMAGE2DPROC glTexImage2D_fun;

#define glGetError glGetError_fun
typedef uint32_t (* PFNGLGETERRORPROC)( void );
extern PFNGLGETERRORPROC glGetError_fun;

#define glUseProgram glUseProgram_fun
typedef void (* PFNGLUSEPROGRAMPROC)( uint32_t program );
extern PFNGLUSEPROGRAMPROC glUseProgram_fun;

#define glCreateProgram glCreateProgram_fun
typedef uint32_t (* PFNGLCREATEPROGRAMPROC)( void );
extern PFNGLCREATEPROGRAMPROC glCreateProgram_fun;

#define glUniform1i glUniform1i_fun
typedef void (* PFNGLUNIFORM1IPROC)( int32_t location, int32_t v0 );
extern PFNGLUNIFORM1IPROC glUniform1i_fun;

#define glGetUniformLocation glGetUniformLocation_fun
typedef int32_t (* PFNGLGETUNIFORMLOCATIONPROC)( uint32_t program, const char * name );
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation_fun;

#define glAttachShader glAttachShader_fun
typedef void (* PFNGLATTACHSHADERPROC)( uint32_t program, uint32_t shader );
extern PFNGLATTACHSHADERPROC glAttachShader_fun;

#define glLinkProgram glLinkProgram_fun
typedef void (* PFNGLLINKPROGRAMPROC)( uint32_t program );
extern PFNGLLINKPROGRAMPROC glLinkProgram_fun;

#define glDeleteShader glDeleteShader_fun
typedef void (* PFNGLDELETESHADERPROC)( uint32_t shader );
extern PFNGLDELETESHADERPROC glDeleteShader_fun;

#define glDetachShader glDetachShader_fun
typedef void (* PFNGLDETACHSHADERPROC)( uint32_t program, uint32_t shader );
extern PFNGLDETACHSHADERPROC glDetachShader_fun;

#define glCreateShader glCreateShader_fun
typedef uint32_t (* PFNGLCREATESHADERPROC)( uint32_t shaderType );
extern PFNGLCREATESHADERPROC glCreateShader_fun;

#define glShaderSource glShaderSource_fun
typedef void (* PFNGLSHADERSOURCEPROC)( uint32_t shader, int32_t count, const char * const * string, const int32_t * length );
extern PFNGLSHADERSOURCEPROC glShaderSource_fun;

#define glCompileShader glCompileShader_fun
typedef void (* PFNGLCOMPILESHADERPROC)( uint32_t shader );
extern PFNGLCOMPILESHADERPROC glCompileShader_fun;

#define glGetShaderiv glGetShaderiv_fun
typedef void (* PFNGLGETSHADERIVPROC)( uint32_t shader, uint32_t pname, int32_t * params );
extern PFNGLGETSHADERIVPROC glGetShaderiv_fun;

#define glGetShaderInfoLog glGetShaderInfoLog_fun
typedef void (* PFNGLGETSHADERINFOLOGPROC)( uint32_t shader, int32_t bufSize, int32_t * length, char * infoLog );
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog_fun;

#define glDrawArrays glDrawArrays_fun
typedef void (* PFNGLDRAWARRAYSPROC)( uint32_t mode, int32_t first, int32_t count );
extern PFNGLDRAWARRAYSPROC glDrawArrays_fun;
