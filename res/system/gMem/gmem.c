# include "gmem.h"

# include <stdlib.h> /* malloc */

typedef long Align;

union header
{
	typedef struct
	{
		unsigned size;
		void* mem;
		union header* next;
	} blockNode;
	Align x;
}

int firstp = -1;

void* gmalloc(unsigned size)
{
	if (firstp == -1)
	{
		firstp = 0;
		
	}
}

void gfree(void* ptr)
{
	
}
