# include "gmem.h"
# include "ctx.h"

# include "stdio.h"

int main(int argc, char** argv)
{
	int* table = 0;
	
	context = create_ctx();
	table = (int*) gmalloc(sizeof(int)*10);	
	gfree(table);
	
	destroy_ctx(context);
	return 0;
}
