#pragma once
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <Winuser.h>
#endif

static inline void xplat_error( const char *format, ... ) __attribute__( ( noreturn ) );
static inline void xplat_error( const char *format, ... )
{
#ifdef _WIN32
// todo: MessageBox or something
#else
    va_list vl;
    va_start( vl, format );
    vprintf( format, vl );
    va_end( vl );
    printf( "\n" );
#endif
    exit( EXIT_FAILURE );
}
