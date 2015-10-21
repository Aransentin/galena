#pragma once
#include <stdint.h>
#include <stdlib.h>

#define vector( TYPE ) \
	struct { TYPE * data; uint32_t n; uint32_t mem; }

// Initialize the vector; only needed if it was declared on the stack
#define vector_init( VEC ) \
	VEC = (__typeof__(VEC)){ .data=0 }

// Free a vector
#define vector_destroy( VEC ) \
	if( (VEC).data != 0 ) { free((VEC).data); }

// Add an undefined variable to the vector
#define vector_add( VEC ) \
	if( (VEC).n == (VEC).mem ) \
		{ (VEC).data = realloc( (VEC).data, ((VEC).mem+32)*sizeof( *((VEC).data) ) ); (VEC).mem+=32; } \
	VEC.n++

// Push a value to the end of the vector
#define vector_push( VEC, VAL ) \
	vector_add( VEC ); \
	(VEC).data[(VEC).n-1] = VAL

// Make sure there are n free members in the vector
#define vector_alloc_limit( VEC, N ) \
	if( (VEC).n+(N) >= (VEC).mem ) \
		{ (VEC).data = realloc( (VEC).data, ((VEC).mem+(N))*sizeof( *((VEC).data) ) ); (VEC).mem+=(N); }
