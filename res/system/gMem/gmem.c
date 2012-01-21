# include "gmem.h"
# include "gmem_private.h"
# define NULL ((void*) 0)

# include <stdio.h>
# include <assert.h>

# include <stdlib.h>
# include <time.h>

# define __DEBUG
# define __MAGIC_NUMBER 1337
# define __GMEM_FUNCTIONAL_TEST_TRIES 1000

typedef long Align;

static char heap[__HEAP_SIZE];

union header
{
	struct
	{
		unsigned magic; /* to check consistency */
		unsigned size;
		union header* next;
		void* mem;
	} blockNode;
	Align x;
};

static union header * firstHdr = NULL;  /* first header to search. It
is guaranteed that it's the littlest address pointer in the free list */
static union header* lastHdr = NULL; /* TODO */

static unsigned hdrSize = sizeof(union header);

void* gmalloc(unsigned size)
{
	static short formatted = 0; /* boolean to know if the heap is formated */
	
	union header * prevHdr = NULL; /* header just before the one to return */
	union header * hdr = NULL; /* the header to return */
	
	unsigned delta;
	unsigned sizeMemNewBlock;
	
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
	
	if (firstHdr == NULL)
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
		union header* newHdr = (union header*)((unsigned)hdr->blockNode.mem + size);
		newHdr->blockNode.mem = (void*)((unsigned)newHdr + hdrSize);
		newHdr->blockNode.size = sizeMemNewBlock;
		
		/* inserts it in the circular linked list */
		newHdr->blockNode.next = (hdr->blockNode.next == hdr) 
									? newHdr 
									: hdr->blockNode.next;
		/* if (prevHdr != NULL && prevHdr != hdr) */ /* TODO */
		if (prevHdr != hdr)
		{
			/* if there is more than one block */
			prevHdr->blockNode.next = newHdr;
		} 
		/* else
		{
			// if there is just one block
			prevHdr = newHdr;
			lastHdr = newHdr;
		} */
		
		if (hdr == lastHdr)
		{
			lastHdr = newHdr;
		}
		
		if (hdr == firstHdr)
		{
			firstHdr = newHdr;
		}
# ifdef __DEBUG
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
			firstHdr = (hdr->blockNode.next != hdr) ? hdr->blockNode.next : NULL;
		}
		
		if (hdr == lastHdr)
		{
			lastHdr = (prevHdr != hdr) ? prevHdr : NULL;
		}
	}
	hdr->blockNode.next = NULL;
	
	/* inits the mem with zeros */
	/* TODO wtf is that malloc bug ?
	{
		char* mem = hdr->blockNode.mem;
		char* maxAddr = (void*)((unsigned)mem + hdr->blockNode.size - 1); // -1
		while(mem < maxAddr)
		{
			*mem++ = 0;
		}
	}
	* */
		
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
{
	union header* hdrToInsert = NULL;
	union header* hdr = NULL;
	union header* hdrIter = NULL;
	short boolMergeWithHdr = 0;
	short boolMergeWithHdrIter = 0;
	/* no ptr means no memory */
	if (ptr == NULL)
	{
		return;
	}
	
	hdrToInsert = (void*)((unsigned)ptr - hdrSize);
	assert(hdrToInsert->blockNode.magic == __MAGIC_NUMBER);
	
	if (firstHdr == NULL)
	{
		firstHdr = hdrToInsert;
		/* prevHdr = hdrToInsert; */
		return;
	}
	
	/* finds the best place to put the header back */
	hdrIter = firstHdr;
	do {		
		hdr = hdrIter;		
		hdrIter = hdrIter->blockNode.next;
		
		if (hdrBeforeHdr(hdr, hdrToInsert))
		{
# ifdef __DEBUG
			printf("[GFREE] hdr(%p) < hdrToInsert(%p)\n",
				(void*) hdr,
				(void*) hdrToInsert);
# endif
			boolMergeWithHdr = 1;
		}
		
		if (hdrBeforeHdr(hdrToInsert, hdrIter))
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
	
	/* We have to merge with the previous one and the next one */
	if (boolMergeWithHdr && boolMergeWithHdrIter)
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
	/* Just merges with the previous one */
	else if (boolMergeWithHdr)
	{
# ifdef __DEBUG
		printf("[GFREE] Merging with the previous one.\n");
# endif
		hdr->blockNode.size += hdrToInsert->blockNode.size + hdrSize;
	}
	/* Just merges with the next one */
	else if (boolMergeWithHdrIter)
	{
# ifdef __DEBUG
		printf("[GFREE] Merging with the next one.\n");
# endif
		hdrToInsert->blockNode.size += hdrIter->blockNode.size + hdrSize;
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
	 * pointers*/
	{	
		short done = 0;
		union header* hdrMin = NULL;
		union header* hdrMax = NULL;
		
		hdrIter = firstHdr;
		do {
			hdr = hdrIter;
			hdrIter = hdrIter->blockNode.next;
			
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
		printf("[GFREE]\tSimple insertion in a list of one element.\n");
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
		printf("[GFREE]\tSimple insertion between 2 sorted elements.\n");
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
		printf("[GFREE]\tSimple insertion at end.\n");
# endif
				hdrToInsert->blockNode.next = hdrMax;
				hdrMax->blockNode.next = hdrToInsert;
				lastHdr = hdrToInsert;
			} else if (hdrMin != NULL && hdrToInsert < hdrMin)
			{
# ifdef __DEBUG
		printf("[GFREE]\tSimple insertion at head.\n");
# endif
				hdrToInsert->blockNode.next = hdrMin;
				lastHdr->blockNode.next = firstHdr = hdrToInsert;
			} else
			{
				/* never should happen */
				printf("[GFREE] Impossible case reached.\n");
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
	printf("[HEADER] Size of mem : %d\n", hdr->blockNode.size);
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
	printf("- Heap : base = %p / end = %p\n", (void*) heap, (void*)((unsigned)heap + __HEAP_SIZE - 1));
	do {
		printf("- Header %d : base = %p / end = %p\n",
			i++, 
			(void*)hdr, 
			(void*)((unsigned)hdr->blockNode.mem + hdr->blockNode.size -1) );
			
		if (i > 10)
		{
			printf("First = %p, HDR = %p, HDR->next = %p\n", (void*) firstHdr, (void*)hdr, (void*) hdr->blockNode.next);
			getchar();
		}
			
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
		== (void*)((unsigned)firstHdr->blockNode.mem + firstHdr->blockNode.size -1));
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
		== (void*)((unsigned)firstHdr->blockNode.mem + firstHdr->blockNode.size -1U));
		
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
	assert(gmem_availableMem() == __HEAP_SIZE - 3*hdrSize - mem3 - mem2);
	
	gmem_fill_tab(table2, size2);
	gmem_fill_tab(table3, size3);
	
	gfree(table2);
	assert(gmem_availableMem() == __HEAP_SIZE - 3*hdrSize - mem3);
	
	gfree(table3);
	assert(gmem_availableMem() == __HEAP_SIZE - hdrSize);
	
	assert(gmem_availableMem() == initialAvailableMem);
	assert(gmem_sizeFreeBlockList() == 1);
	
	assert((void*)((unsigned)heap + __HEAP_SIZE - 1)
		== (void*)((unsigned)firstHdr->blockNode.mem + firstHdr->blockNode.size -1));
		
	printf("Test 2 : OK.\n");
}

void gmem_test3()
{
	int *table[10];
	short boolMemAllocated[10];
	int i;
	int sizeOfOneTable = 4;
	unsigned memSize = sizeof(int)*sizeOfOneTable;
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
			printf("\t\tMalloc.\n");
			table[j] = (int*) gmalloc(memSize);
			assert(table[j] != NULL);
			gmem_fill_tab(table[j], sizeOfOneTable);
			boolMemAllocated[j] = 1;
		}
		gmem_show_heap();
		/* (); */
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
	assert((void*)((unsigned)heap + __HEAP_SIZE - 1)
		== (void*)((unsigned)firstHdr->blockNode.mem + firstHdr->blockNode.size -1));
		
	printf("Test 3 : OK.\n");
}
