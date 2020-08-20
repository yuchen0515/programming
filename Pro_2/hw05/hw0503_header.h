#pragma once

#include <stdio.h>
#include <stdint.h>

#if defined(DEBUG_LEVEL_NONE)
	#define DEBUG_LEVEL 0
	#undef DEBUG_LEVEL_NONE
#elif defined(DEBUG_LEVEL_ERROR)
	#define DEBUG_LEVEL 1
	#undef DEBUG_LEVEL_ERROR
#elif defined(DEBUG_LEVEL_INFO)
	#define DEBUG_LEVEL 2
	#undef DEBUG_LEVEL_INFO
#elif defined(DEBUG_LEVEL_VERBOSE)
	#define DEBUG_LEVEL 3
	#undef DEBUG_LEVEL_VERBOSE
#elif defined(DEBUG_LEVEL_VVERBOSE)
	#define DEBUG_LEVEL 4
	#undef DEBUG_LEVEL_VVERBOSE
#else 
	#define DEBUG_LEVEL 0
#endif

#define DEBUG_LEVEL_NONE 0
#define DEBUG_LEVEL_ERROR 1
#define DEBUG_LEVEL_INFO 2
#define DEBUG_LEVEL_VERBOSE 3
#define DEBUG_LEVEL_VVERBOSE 4

#define debug_print(level,fmt,...)\
	do {if(level<=DEBUG_LEVEL && level !=0)\
		fprintf(stderr,"%s:%d:%s(): "fmt,\
				__FILE__, __LINE__, __func__, __VA_ARGS__ );}\
				while (0);

