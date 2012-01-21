# include "gmem.h"
# include "gmem_private.h"

# include "assert.h"
# include "stdio.h"

typedef void (*TestFunction) (void);

static TestFunction testFunctions[] = {gmem_test0, 
									   gmem_test1,
									   gmem_test2,
									   gmem_test3};
static int numberOfTestFunctions = 4;


int main(int argc, char** argv)
{	
	int i;
	for (i = 0; i < numberOfTestFunctions; ++i)
	{
		testFunctions[i]();
		gmem_show_heap();
	}
	
	printf("Every tests are OK\n\n");

	return 0;
}
