# include "gmem.h"
# include <stdlib.h>	/* NULL, srand, rand... */

/* Uncomment this if you want to see a lot of debug messages when
 * using the functions.
 **/
/* # define __DEBUG */
 
/*
 * Magic number, used in structures to check coherency. This allows to
 * detect heap corruptions and checks that ptr given to gfree have been
 * allocated with gmalloc.
 */
# define __MAGIC_NUMBER 1337

# ifdef USE_MALLOC 
/* STDLIB implementation */
void* gmalloc(unsigned size)
{
	return malloc(size);
}

void gfree(void* ptr)
{
	free(ptr);
}
# else

# include "gmem_private.h"	/* tests */

# include <stdio.h>		/* printf() */
# include <assert.h>	/* assert() */
# include <time.h>		/* time() */

/*
 * Used to align headers on word, in order to optimize execution.
 * (cf Kernighan & Ritchie's C Programming Language)
 */
typedef long Align;

/*
 * Scoop : the heap is in fact a fixed-size char table.
 */
static char heap[__HEAP_SIZE];

/*
 * Union header, which contains the struct describing a header and is
 * aligned.
 */
union header
{
	struct
	{
		unsigned magic; 	/* used to check consistency */
		unsigned size;		/* size of the memory given */
		union header* next; /* next header in the circular list */
		void* mem;			/* pointer on memory */
	} blockNode;
	Align x;
};

/*
 * The headers descripting free memory are put in a circular chained 
 * list, sorted by pointer address, in order to optimize merging when 
 * freeing.
 */
static union header * firstHdr = NULL;  /* first header to search
(littlest address). */
static union header* lastHdr = NULL; /* last header to search (biggest
address). */

static unsigned hdrSize = sizeof(union header); /* size of an header*/

void* gmalloc(unsigned size)
{
	static short formatted = 0; /* boolean to know if the heap is 
	formatted. Is just done once at the first gmalloc. */
	
	union header * prevHdr = NULL; /* header just before the one to 
	return */
	union header * hdr = NULL; /* the header to return */
	
	/* These two variables are used later to know if it's interesting
	 * to split the block.
	 */
	int delta;
	int sizeMemNewBlock;
	
	if (!formatted)
	{
		formatted = 1;
		/* format heap */
		firstHdr = (union header*) heap;
		firstHdr->blockNode.size = __HEAP_SIZE - hdrSize;
		firstHdr->blockNode.next = firstHdr;
		firstHdr->blockNode.mem = (void*)((unsigned)firstHdr + hdrSize);
		lastHdr = prevHdr = firstHdr;
	}
	
	/* firstHdr is NULL only when all the memory has been used */
	if (size == 0U || firstHdr == NULL)
	{
		return NULL;
	}
	
	hdr = firstHdr;
	prevHdr = lastHdr;
	/* First fit : finds the first sufficiently big block after the last
	 * used position */
	while(hdr->blockNode.size < size)
	{
		prevHdr = hdr;
		hdr = hdr->blockNode.next;
		if (hdr == firstHdr)
		/* Two cases :
		 * - Just one node in the list, we're in the while so there's
		 * not enough memory => return NULL
		 * - More than one node : we've make a whole "turn" in the list
		 * => no block has enough memory => return NULL
		 * */
		{
			return NULL;
		}
	}
	/* from this line, we have a good block */

	/* splits the block if it is bigger than the size asked */
	delta = hdr->blockNode.size - size;
	sizeMemNewBlock = delta - hdrSize;
	
	if (hdr->blockNode.size > size && sizeMemNewBlock > 0)
	{
		/* "Creates" a new header */
		union header* newHdr = (union header*)
								((unsigned)hdr->blockNode.mem + size);
		newHdr->blockNode.mem = (void*)((unsigned)newHdr + hdrSize);
		newHdr->blockNode.size = sizeMemNewBlock;
		
		/* inserts it in the circular linked list */
		newHdr->blockNode.next = (hdr->blockNode.next == hdr) 
									? newHdr 
									: hdr->blockNode.next;
		if (hdr != prevHdr)
		{
			/* if there is more than one block */
			prevHdr->blockNode.next = newHdr;
		}
		
		if (hdr == lastHdr)
		{
			lastHdr = newHdr;
		}
		
		if (hdr == firstHdr)
		{
			firstHdr = newHdr;
		}
# ifdef __DEBUG
		printf("[GMALLOC] Delta = %d, sizeOfNew = %d\n", 
				delta, sizeMemNewBlock);
		printf("[GMALLOC] A new block has been created :\n");
		gmem_printHeader(newHdr->blockNode.mem);
# endif	
		hdr->blockNode.size = size;
	} else
	/* just removes the block */
	{			
		if (hdr != prevHdr)
		{
			prevHdr->blockNode.next = hdr->blockNode.next;
		}
		
		if (hdr == firstHdr)
		{
			firstHdr = (hdr->blockNode.next != hdr) ?hdr->blockNode.next
													: NULL;
		}
		
		if (hdr == lastHdr)
		{
			lastHdr = (prevHdr != hdr) ? prevHdr : NULL;
		}
	}
	hdr->blockNode.next = NULL;
	
	/* inits the mem with zeros */
	{
		char* mem = hdr->blockNode.mem;
		char* maxAddr = (void*)((unsigned)mem + hdr->blockNode.size);
		while(mem < maxAddr)
		{
			*mem++ = 0;
		}
	}
		
# ifdef __DEBUG
	printf("[GMALLOC] Returned block :\n");
	gmem_printHeader(hdr->blockNode.mem);
# endif
	
	/* saves magic number */
	hdr->blockNode.magic = __MAGIC_NUMBER;
	/* returns the memory */
	return (void*) hdr->blockNode.mem;
}

/*
 * Returns true if hdr2 is just after hdr1
 */
static short hdrBeforeHdr(union header* hdr1, union header* hdr2)
{
	return ((unsigned)hdr1->blockNode.mem + hdr1->blockNode.size
			== (unsigned)hdr2);
}

void gfree(void* ptr)
/* We look for a place to put the header, then we put it. */
{
	union header* hdrToInsert = NULL;	/* header associated to ptr */
	union header* hdr = NULL;			/* header before the place to 
	insert */
	union header* hdrIter = NULL;		/* header just after the place
	to insert */
	
	short boolMergeWithHdr = 0; /* indicates whether we need a merge 
	with the previous one or not. */
	short boolMergeWithHdrIter = 0; /* indicates whether we need a 
	merge with the next one or not. */
	
	if (ptr == NULL)
	/* no ptr means nothing to do */
	{
		return;
	}
	
	hdrToInsert = (void*)((unsigned)ptr - hdrSize);
	if (hdrToInsert->blockNode.magic != __MAGIC_NUMBER)
	/* fatal error : heap could have been corrupted (segfault) */
	{
		fprintf(stderr, 
				"Fatal error : corrupted heap when call to free.\n");
		exit(1);
	}
	
	if (firstHdr == NULL)
	{
		lastHdr = firstHdr = hdrToInsert;
		return;
	}
	
	/* finds the best place to put the header back */
	hdrIter = firstHdr;
	do {		
		hdr = hdrIter;		
		hdrIter = hdrIter->blockNode.next;
		
		if (hdrBeforeHdr(hdr, hdrToInsert))
		/* we can merge with the previous one */
		{
# ifdef __DEBUG
			printf("[GFREE] hdr(%p) < hdrToInsert(%p)\n",
				(void*) hdr,
				(void*) hdrToInsert);
# endif
			boolMergeWithHdr = 1;
		}
		
		if (hdrBeforeHdr(hdrToInsert, hdrIter))
		/* we can merge with the next one */
		{
# ifdef __DEBUG
			printf("[GFREE] hdrToInsert(%p) < hdrIter(%p)\n",
				(void*) hdrToInsert,
				(void*) hdrIter);
# endif
			boolMergeWithHdrIter = 1;
		}
	}
	while (!boolMergeWithHdr && !boolMergeWithHdrIter 
			&& hdrIter != firstHdr);
	
	if (boolMergeWithHdr && boolMergeWithHdrIter)
	/* We have to merge with the previous one and the next one */
	{
# ifdef __DEBUG
		printf("[GFREE] Merging with previous and next ones.\n");
# endif
		hdr->blockNode.size += hdrToInsert->blockNode.size + hdrSize;
		hdr->blockNode.size += hdrIter->blockNode.size + hdrSize;
		hdr->blockNode.next = hdrIter->blockNode.next;
		
		if (hdrIter == lastHdr)
		{
			lastHdr = hdr;
		}
	}
	else if (boolMergeWithHdr)
	/* Just merges with the previous one */
	{
# ifdef __DEBUG
		printf("[GFREE] Merging with the previous one.\n");
# endif
		hdr->blockNode.size += hdrToInsert->blockNode.size + hdrSize;
	}
	else if (boolMergeWithHdrIter)
	/* Just merges with the next one */
	{
# ifdef __DEBUG
		printf("[GFREE] Merging with the next one.\n");
# endif
		hdrToInsert->blockNode.size += hdrIter->blockNode.size +hdrSize;
		hdrToInsert->blockNode.next = 
			(hdrIter->blockNode.next != hdrIter) ?
				hdrIter->blockNode.next :
				hdrToInsert;
				
		if (hdrIter == firstHdr)
		{
			firstHdr = hdrToInsert;
		}
		if (hdrIter == lastHdr)
		{
			lastHdr = hdrToInsert;
		}
		
		hdr->blockNode.next = hdrToInsert;
	}
	else
	/* No cool place has been found, just puts it in increasing order of
	 * pointers. We have to look another time for the best place, by
	 * looking at addresses. */
	/* TODO : the place to insert could be searched the first time. */
	{	
		short done = 0;	/* boolean to know if we're done */
		union header* hdrMin = NULL; /* the littlest address */
		union header* hdrMax = NULL; /* the biggest address */
		
		hdrIter = firstHdr;
		do {
			hdr = hdrIter;
			hdrIter = hdrIter->blockNode.next;
			
			/* Looks for the littlest and biggest addresses */
			if (hdrMin == NULL || hdr < hdrMin)
			{
				hdrMin = hdr;
			}
			if (hdrMax == NULL || hdr > hdrMax)
			{
				hdrMax = hdr;
			}
			
			if (hdr == hdrIter)
			/* if there's just one element */
			{
# ifdef __DEBUG
		printf("[GFREE] Simple insertion in a list of one element.\n");
# endif
				hdrToInsert->blockNode.next = hdr;
				hdr->blockNode.next = hdrToInsert;
				if (hdrToInsert < hdr)
				{
					firstHdr = hdrToInsert;
				} else
				{
					lastHdr = hdrToInsert;
				}
				done = 1;
			} else if (hdr < hdrToInsert && hdrToInsert < hdrIter)
			/* there are at least two elements and they're sorted */
			{
# ifdef __DEBUG
		printf("[GFREE] Simple insertion between 2 sorted elements.\n");
# endif
				hdrToInsert->blockNode.next = hdr->blockNode.next;
				hdr->blockNode.next = hdrToInsert;
				done = 1;
			}
		} while (!done && hdrIter != firstHdr);
		
		if (!done)
		/* must put the header in the head or end of list */
		{
			if (hdrMax != NULL && hdrToInsert > hdrMax)
			{
# ifdef __DEBUG
		printf("[GFREE] Simple insertion at end.\n");
# endif
				hdrToInsert->blockNode.next = hdrMax;
				hdrMax->blockNode.next = hdrToInsert;
				lastHdr = hdrToInsert;
			} else if (hdrMin != NULL && hdrToInsert < hdrMin)
			{
# ifdef __DEBUG
		printf("[GFREE] Simple insertion at head.\n");
# endif
				hdrToInsert->blockNode.next = hdrMin;
				lastHdr->blockNode.next = firstHdr = hdrToInsert;
			} else
			{
				/* never should happen */
				fprintf(stderr, "[GFREE] Impossible case reached.\n");
				exit(1);
			}
		}
	}
}

void gmem_printHeader(void* ptr)
{
	union header* hdr = NULL;
	
	if (ptr == NULL)
		return;
		
	hdr = (void*)((unsigned)ptr - hdrSize);
	printf("\n");
	printf("[HEADER] Pointer : %p\n", ptr);
	printf("[HEADER] Header : %p\n", hdr);
	printf("[HEADER] Size of mem : %u\n", hdr->blockNode.size);
	printf("[HEADER] Adress of mem : %p\n", hdr->blockNode.mem);
	printf("[HEADER] Next header adress : %p\n", hdr->blockNode.next);
	printf("\n");
}

int gmem_sizeFreeBlockList()
{
	union header* hdr = firstHdr;
	if (hdr == NULL)
		return 0;
	else
	{
		int size = 0;
		do {
			++size;
			hdr = hdr->blockNode.next;
		} while (hdr != firstHdr);
		return size;
	}
}

unsigned gmem_availableMem()
{
	union header* hdr = firstHdr;
	if (hdr == NULL)
		return 0U;
	else
	{
		unsigned availableMem = 0U;
		do {
			availableMem += hdr->blockNode.size;
			hdr = hdr->blockNode.next;
		} while (hdr != firstHdr);
		return availableMem;
	}
}

void gmem_show_heap()
{
	int i = 0;
	union header* hdr = firstHdr;
	printf("\n\n----- HEAP -----\n");
	printf("- Available memory : %d\n", gmem_availableMem());
	printf("- Heap : base = %p / end = %p\n", 
				(void*) heap, 
				(void*)((unsigned)heap + __HEAP_SIZE - 1));
	do {
		printf("- Header %d : base = %p / mem = %d / end = %p\n",
			i++, 
			(void*)hdr, 
			hdr->blockNode.size,
			(void*)
			((unsigned)hdr->blockNode.mem + hdr->blockNode.size -1) );
				
		hdr = hdr->blockNode.next;
	} while (hdr != firstHdr);
	printf("----- END OF HEAP -----\n\n");
}

/******************************** TESTS *******************************/
void gmem_test0()
{
	printf("Test 0 : running.\n");
	assert(gmalloc(__HEAP_SIZE+1) == NULL);
	assert(gmem_sizeFreeBlockList() == 1);
	
	assert((void*)((unsigned)heap + __HEAP_SIZE - 1)
		== (void*)((unsigned)firstHdr->blockNode.mem 
					+ firstHdr->blockNode.size -1));
	printf("Test 0 : OK.\n");
}

/* This function is here to ensure that there is no SEGFAULT. 
 * Indeed, if whe try to write on an address which is bigger than end
 * of heap, there'll be a SEGFAULT. The magic number ensures, by another
 * way, that allocations just concern the given segment.
 * */
static void gmem_fill_tab(int* table, int size)
{
	int i;
	for (i = 0U; i < size; ++i)
	{
		table[i] = i;
	}
}

void gmem_test1()
{
	int* table = 0;
	int tableSize = 64;
	unsigned mem1 = sizeof(int)*tableSize;
	unsigned initialAvailableMem = gmem_availableMem();
	
	printf("Test 1 : running.\n");
	
	table = (int*) gmalloc(mem1);
	assert(table != NULL);
	assert(gmem_availableMem() == __HEAP_SIZE - 2*hdrSize - mem1);
	
	gmem_fill_tab(table, tableSize);
	
	gfree(table);
	
	assert(gmem_availableMem() == initialAvailableMem);
	assert(gmem_sizeFreeBlockList() == 1);

	assert((void*)((unsigned)heap + (unsigned)__HEAP_SIZE - 1U)
		== (void*)((unsigned)firstHdr->blockNode.mem 
		+ firstHdr->blockNode.size 
		-1U));
		
	printf("Test 1 : OK.\n");
}

void gmem_test2()
{	
	int *table2 = 0, *table3 = 0;
	int size2 = 8, size3 = 16;
	unsigned mem2 = sizeof(int)*size2;
	unsigned mem3 = sizeof(int)*size3;
	unsigned initialAvailableMem = gmem_availableMem();
	
	printf("Test 2 : running.\n");
	
	table2 = (int*) gmalloc(mem2);
	assert(table2 != NULL);
	assert(gmem_availableMem() == __HEAP_SIZE - 2*hdrSize - mem2);
	
	table3 = (int*) gmalloc(mem3);
	assert(table3 != NULL);
	assert(gmem_availableMem() == __HEAP_SIZE - 3*hdrSize - mem3 -mem2);
	
	gmem_fill_tab(table2, size2);
	gmem_fill_tab(table3, size3);
	
	gfree(table2);
	assert(gmem_availableMem() == __HEAP_SIZE - 3*hdrSize - mem3);
	
	gfree(table3);
	assert(gmem_availableMem() == __HEAP_SIZE - hdrSize);
	
	assert(gmem_availableMem() == initialAvailableMem);
	assert(gmem_sizeFreeBlockList() == 1);
	
	assert((void*)((unsigned)heap + __HEAP_SIZE - 1U)
		== (void*)((unsigned)firstHdr->blockNode.mem 
					+ firstHdr->blockNode.size - 1U));
		
	printf("Test 2 : OK.\n");
}

void gmem_test3()
{
	int *table[10];
	short boolMemAllocated[10];
	int i;
	int size[4] = {4U, 6U, 8U, 10U};
	unsigned initialAvailableMem = gmem_availableMem();
	
	printf("Test 3 : running.\n");
	
	for (i = 0; i < 10; ++i)
	{
		table[i] = NULL;
		boolMemAllocated[i] = 0;
	}
	
	srand(time(NULL));
	
	for (i = 0; i < __GMEM_FUNCTIONAL_TEST_TRIES; ++i)
	{
		int j = rand() % 10;
		printf("\tFunctional %d running\n", i);
		
		if (boolMemAllocated[j])
		{
			printf("\t\tFree.\n");
			gfree(table[j]);
			boolMemAllocated[j] = 0;
		} else
		{
			int sizeChosen = size[rand()%4];
			unsigned memSize = sizeof(int)*sizeChosen;
			printf("\t\tMalloc of %d.\n", memSize);
			table[j] = (int*) gmalloc(memSize);
			assert(table[j] != NULL);
			gmem_fill_tab(table[j], sizeChosen);
			boolMemAllocated[j] = 1;
		}
# ifdef __DEBUG
		gmem_show_heap();
# endif
	}
	
	for (i = 0; i < 10; ++i)
	{
		if (boolMemAllocated[i])
		{
			gfree(table[i]);
		}
	}
	
	assert(gmem_availableMem() == initialAvailableMem);
	assert(gmem_sizeFreeBlockList() == 1);
	assert((void*)((unsigned)heap + __HEAP_SIZE - 1U)
		== (void*)((unsigned)firstHdr->blockNode.mem 
						+ firstHdr->blockNode.size 
						- 1U));
		
	printf("Test 3 : OK.\n");
}

# endif
