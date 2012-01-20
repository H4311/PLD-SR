# include "gmem.h"
# include "ctx.h"

# include "assert.h"
# include "stdio.h"

int main(int argc, char** argv)
{
	int* table = 0;
	int i = 0;
	
	context = create_ctx();
	
	table = (int*) gmalloc(__HEAP_SIZE);
	assert(table == NULL);
	
	table = (int*) gmalloc(sizeof(int)*64);
	
	for(; i < 64; ++i)
	{
		printf("%d) %d\n", i, table[i]);
	}
	
	assert(table != NULL);
	
	gfree(table);
	
	destroy_ctx(context);

	return 0;
}
