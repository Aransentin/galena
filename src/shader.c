#include "shader.h"
#include "engine.h"
#include "xplat.h"

static const char *shader_vert = "#version 330\n"
                                 "layout(location = 0) in vec2 vPos;\n"
                                 "out vec2 fUV;\n"
                                 "void main( void )\n"
                                 "{\n"
                                 "	fUV = vPos*0.5 + vec2( 0.5, 0.5 );\n"
                                 "	gl_Position = vec4( vPos, 0.0, 1.0 );\n"
                                 "}\n"
                                 "";

static const char *shader_frag = "#version 330\n"
                                 "layout(location = 0) out vec4 oCol;\n"
                                 "in vec2 fUV;\n"
                                 "uniform sampler2D rTex;\n"
                                 "void main( void )\n"
                                 "{\n"
                                 "	oCol = vec4( texture( rTex, fUV ).rgb, 1.0 );\n"
                                 "}\n"
                                 "";

static uint32_t shader_program_load( uint32_t type, const char *src )
{
    uint32_t s = glCreateShader( type );
    glShaderSource( s, 1, &src, NULL );
    glCompileShader( s );

    int32_t status;
    glGetShaderiv( s, GL_COMPILE_STATUS, &status );
    if ( status != GL_TRUE )
    {
        char buffer[1024] = {0};
        glGetShaderInfoLog( s, 1024, NULL, buffer );
        printf( "Shader compile error: %s", buffer );
        exit( EXIT_FAILURE );
    }
    return s;
}

uint32_t shader_load( void )
{
    uint32_t program = glCreateProgram();
    uint32_t vs = shader_program_load( GL_VERTEX_SHADER, shader_vert );
    uint32_t fs = shader_program_load( GL_FRAGMENT_SHADER, shader_frag );
    glAttachShader( program, vs );
    glAttachShader( program, fs );
    glLinkProgram( program );
    glDetachShader( program, vs );
    glDetachShader( program, fs );
    glDeleteShader( vs );
    glDeleteShader( fs );

    glUseProgram( program );
    glUniform1i( glGetUniformLocation( program, "rTex" ), 0 );
    return program;
}
