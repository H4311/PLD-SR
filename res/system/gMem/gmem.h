# ifndef __GMEM_H__
# define __GMEM_H__

# include "gmem_interface.h"

/* #define USE_MALLOC */
# ifdef USE_MALLOC
	#include <stdlib.h>
	#define gmalloc malloc
	#define gfree free
# else
	void* gmalloc(unsigned size);
	void gfree(void* ptr);
# endif

void init_mem(ctx_s* pctx);
void destroy_mem(ctx_s* pctx);

# endif
