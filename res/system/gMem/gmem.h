# ifndef __GMEM_H__
# define __GMEM_H__

# define __HEAP_SIZE 512

/* #define USE_MALLOC */
# ifdef USE_MALLOC
	#include <stdlib.h>
	#define gmalloc malloc
	#define gfree free
# else
	void* gmalloc(unsigned size);
	void  gfree(void* ptr);
# endif

# endif
