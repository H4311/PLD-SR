# include "gmem.h"
# include "ctx.h"

# include "assert.h"
# include "stdio.h"

int main(int argc, char** argv)
{
	int* table = 0;
	
	context = create_ctx();
	
	table = (int*) gmalloc(__HEAP_SIZE);
	assert(table == NULL);
	
	table = (int*) gmalloc(256);
	/*
	for(; i < 256; ++i)
	{
		printf("%d) %d\n", i, table[i]);
	}
	* */
	assert(table != NULL);
	gmem_printHeader(table);
	
	gfree(table);
	
	destroy_ctx(context);

	return 0;
}
