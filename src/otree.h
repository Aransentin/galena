#pragma once
#include <stdint.h>

typedef struct{
	union{
		uint32_t p;
		struct{
			uint8_t p1, p2, p3;
			uint8_t bf;
		};
	};
} OTnode_cl;
