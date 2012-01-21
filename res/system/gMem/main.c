# include "gmem.h"
# include "gmem_private.h"

# include "assert.h"
# include "stdio.h"
# include "math.h"

struct prime {
	int p;
	struct prime* next;
} ;

typedef void (*TestFunction) (void);

static TestFunction testFunctions[] = {gmem_test0, 
									   gmem_test1,
									   gmem_test2,
									   gmem_test3};
static int numberOfTestFunctions = 4;

/* Test main */
int main(int argc, char** argv)
{	
	int i;
	struct prime *two, *three, *p;
	
# ifndef USE_MALLOC
	for (i = 0; i < numberOfTestFunctions; ++i)
	{
		testFunctions[i]();
		gmem_show_heap();
	}
	printf("Every tests are OK\n\n");
# endif

	two = (struct prime*) gmalloc(sizeof(struct prime)), 
	three = (struct prime*) gmalloc(sizeof(struct prime)),
	
	two->p = 2;
	two->next = three;
	three->p = 3;
	three->next = NULL;
	
	for (i = 4; i < 100000; ++i)
	{
		struct prime* p;
		short boolIsPrime = 1;
		for (p = two; p != NULL && p->p <= sqrt(i) && boolIsPrime; p = p->next)
		{
			if (i % p->p == 0)
			{
				boolIsPrime = 0;
			}
		}
		
		if (boolIsPrime)
		{
			struct prime* p;
			struct prime* newPrime = gmalloc(sizeof(struct prime));
			newPrime->p = i;
			newPrime->next = NULL;
			for (p = two; p->next != NULL; p = p->next)
			{
				/* empty :) */
			}
			p->next = newPrime;
		}
	}
	
	p = two;
	while(p != NULL)
	{
		struct prime* temp = p->next;
		printf("%d ", p->p);
		gfree(p);
		p = temp;
	}
	printf("\n");
		
	return 0;
}
