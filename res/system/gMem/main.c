# include "gmem.h"
# include "ctx.h"

# include "assert.h"
# include "stdio.h"

int main(int argc, char** argv)
{
	int* table = 0, *table2 = 0, *table3 = 0;
	
	context = create_ctx();
	
	table = (int*) gmalloc(__HEAP_SIZE+1);
	assert(table == NULL);
	
	table = (int*) gmalloc(sizeof(int)*64); /* 4*64 = 256 */
	assert(table != NULL);
	
	/*
	{
		int i = 0;
		for(; i < 64; ++i)
		{
			printf("%d) %d\n", i, table[i]);
		}
	}
	*/
	
	printf("Available memory : %d\n", gmem_availableMem());
	/* 512 - 256 - 2*12 */
	
	table2 = (int*) gmalloc(sizeof(int)*8); /* 4*8 = 32 */
	assert(table2 != NULL);
	
	printf("Before free(table), available memory : %d\n", gmem_availableMem());
	/* 512 - 256 - 32 - 3*12 */
	
	gfree(table);
	printf("After free(table), available memory : %d\n", gmem_availableMem());
	/* 512 - 32 - 3*12 */
	
	table3 = (int*) gmalloc(sizeof(int)*8); /* 32 */
	assert(table3 != NULL);
	printf("After table3.malloc(), available memory : %d\n", gmem_availableMem());
	/* 512 - 32 - 32 - 4*12 */
	
	gfree(table3);
	printf("After free(table3), available memory : %d\n", gmem_availableMem());
	/* 512 - 32 - 4*12 */
	
	gfree(table2);
	printf("After free(table2), available memory : %d\n", gmem_availableMem());
	/* 512 - 4*12 */
	
	destroy_ctx(context);

	return 0;
}
