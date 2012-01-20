# include "gmem.h"
# include "ctx.h"
# define NULL ((void*) 0)

# define __DEBUG
# ifdef __DEBUG
# include <stdio.h>
# endif

typedef long Align;

union header
{
	struct
	{
		unsigned size;
		union header* next;
		void* mem;
	} blockNode;
	Align x;
};

static union header * firstHdr = NULL;  /* first header to search */
static union header * prevHdr = NULL; /* header just before the one to return */
static unsigned hdrSize = sizeof(union header);

void* gmalloc(unsigned size)
{
	static short notFormated = 1; /* boolean to know if the heap is formated */
	
	union header * hdr = NULL; /* the header to return */
	
	if (notFormated)
	{
		notFormated = 0;
		/* format heap */
		firstHdr = (union header*) __CURRENT_CONTEXT->heap;
		firstHdr->blockNode.size = __HEAP_SIZE - hdrSize;
		firstHdr->blockNode.next = firstHdr;
		firstHdr->blockNode.mem = (void*)((unsigned)firstHdr + hdrSize);
		prevHdr = firstHdr;
	}
	
	if (firstHdr == NULL)
	{
		return NULL;
	}
	
	hdr = firstHdr;
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
	if (hdr->blockNode.size > size)
	{
		unsigned delta = hdr->blockNode.size - size;
		unsigned sizeMemNewBlock = delta - hdrSize;
		if (sizeMemNewBlock > 0)
		{
			/* "Creates" a new header */
			union header* newHdr = (union header*)((unsigned)hdr->blockNode.mem + size);
			newHdr->blockNode.mem = (void*)((unsigned)newHdr + hdrSize);
			newHdr->blockNode.size = sizeMemNewBlock;
			
			/* inserts it in the circular linked list */
			newHdr->blockNode.next = (hdr->blockNode.next == hdr) ? newHdr : hdr->blockNode.next;
			if (prevHdr != hdr)
			{
				/* if there is more than one block */
				prevHdr->blockNode.next = newHdr;
			} else
			{
				/* if there is just one block */
				prevHdr = newHdr;
			}
			
			firstHdr = newHdr;
# ifdef __DEBUG
			printf("[GMALLOC] A new block has been created :\n");
			gmem_printHeader(newHdr->blockNode.mem);
# endif	
			
			hdr->blockNode.size = size;
		}
	} else
	/* just removes the block */
	{
		firstHdr = (hdr->blockNode.next != hdr) ? hdr->blockNode.next : NULL;
		if (prevHdr != hdr)
		{
			prevHdr->blockNode.next = hdr->blockNode.next;
		} else
		{
			/* if there was just one block, there is no more previous */
			prevHdr = NULL;
		}
	}
	hdr->blockNode.next = NULL;
	
	/* inits the mem with zeros */
	{
		char* mem = hdr->blockNode.mem;
		char* maxAddr = (void*)((unsigned)mem + hdr->blockNode.size - 1);
		while(mem < maxAddr)
		{
			*mem++ = 0;
		}
	}
		
# ifdef __DEBUG
	printf("[GMALLOC] Returned block :\n");
	gmem_printHeader(hdr->blockNode.mem);
# endif
	
	/* returns the memory */
	return (void*) hdr->blockNode.mem;
}

void gfree(void* ptr)
{
	union header* hdrToInsert = NULL;
	union header* hdr = NULL;
	/* no ptr means no memory */
	if (ptr == NULL)
	{
		return;
	}
	
	hdrToInsert = (void*)((unsigned)ptr - hdrSize);
	
	if (firstHdr == NULL)
	{
		firstHdr = hdrToInsert;
		prevHdr = hdrToInsert;
		return;
	}
	
	/* finds the best place to put the header back */
	hdr = firstHdr;
	
	/* puts it */
	hdrToInsert->blockNode.next = hdr->blockNode.next;
	hdr->blockNode.next = hdrToInsert;
	
	prevHdr = hdr;
	firstHdr = hdrToInsert;
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
