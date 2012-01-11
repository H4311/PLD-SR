# include "gmem.h"
# include "ctx.h"

# include "assert.h"
# include "stdio.h"

int main(int argc, char** argv)
{
	int* table = 0;
	
	context = create_ctx();
	
	table = (int*) gmalloc(1023);
	assert(table != NULL);
	gfree(table);
	
	table = (int*) gmalloc(1);
	assert(table != NULL);
	gfree(table);
	
	destroy_ctx(context);
	return 0;
}
