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
		char* mem;
		union header* next;
	} blockNode;
	Align x;
};

unsigned hdrSize = sizeof(union header);

void* gmalloc(unsigned size)
{
	static union header * firstHeader = NULL;  /* first header to search */
	union header * hdr = NULL; /* the header to return */
	union header * prevHdr = NULL; /* header just before the one to return */
	unsigned i;
	
	if (firstHeader == NULL)
	{
		/* format heap */
		firstHeader = (union header*) __CURRENT_CONTEXT->heap;
		firstHeader->blockNode.size = __HEAP_SIZE - hdrSize;
		firstHeader->blockNode.next = firstHeader;
		
		firstHeader->blockNode.mem = (void*)((unsigned)firstHeader + hdrSize);
	}
	
	hdr = firstHeader;
	/* First fit : finds the first block after the last used position */
	while(hdr->blockNode.size < size)
	{
		prevHdr = hdr;
		hdr = hdr->blockNode.next;
		if (hdr == firstHeader)
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

	/* splits the block if it is bigger than the size asked */
	/*
	if (hdr->blockNode.size > size)
	{
		unsigned delta = hdr->blockNode.size - size;
		unsigned sizeNewHdr = delta - hdrSize;
		if (sizeNewHdr > 0)
		{
			// "Creates" a new header
			union header* newHdr = hdr->blockNode.mem + size;
			newHdr->blockNode.mem = newHdr + hdrSize;
			newHdr->blockNode.size = sizeNewHdr;
			
			// inserts it in the circular linked list
			newHdr->blockNode.next = (hdr->blockNode.next == hdr) ? newHdr : hdr->blockNode.next;
			if (prevHdr != NULL)
			{
				prevHdr->blockNode.next = newHdr;
			}
			
			firstHeader = newHdr;
			# ifdef __DEBUG
			printf("[GMALLOC] A new block has been created.\n");
			gmem_printHeader(hdr->blockNode.mem);
			gmem_printHeader(newHdr->blockNode.mem);
			# endif	
			
			hdr->blockNode.size = size;
			hdr->blockNode.next = NULL;
		}
	}
	*/
	
	/* inits the mem with zeros */
	/* TODO wtf is that malloc bug ?
	{
		char* mem = hdr->blockNode.mem;
		char* maxAddr = (int) mem + (int) hdr->blockNode.size - 1;
		int i = 0;
		printf("mem = %d / maxAddr = %d\n", mem, maxAddr);
		while(mem < maxAddr)
		{
			*mem++ = 0;
			printf("mem = %d / maxAddr = %d\n", mem, maxAddr);
		}
	}
	*/
	
	printf("[HEADER] Pointer : %x\n", hdr->blockNode.mem);
	printf("[HEADER] Header : %x\n", hdr);
	printf("\n");
	printf("Valeur de pmem == hdr + hdrSize : %x\n", hdr + hdrSize);
	printf("Valeur de hdr == pmem - hdrSize : %x\n", (hdr->blockNode.mem) - hdrSize);
	
	gmem_printHeader(hdr->blockNode.mem);
	
	/* returns the memory */
	return (void*) hdr->blockNode.mem;
}

void gfree(void* ptr)
{
	union header* hdr = NULL;
	/* no ptr means no memory */
	if (ptr == NULL)
	{
		return;
	}
	
	hdr = ptr - hdrSize;
	
# ifdef __DEBUG
	printf("[GFREE] Memory used : %d\n", hdr->blockNode.size);
# endif
	
	/* finds the best place to put the header back */
	
	/* puts it */
}

void gmem_printHeader(void* ptr)
{
# ifdef __DEBUG
	union header* hdr = NULL;
	
	if (ptr == NULL)
		return;
		
	hdr = ptr - (void*)hdrSize;
	printf("\n");
	printf("[HEADER] Pointer : %x\n", ptr);
	printf("[HEADER] Header : %x\n", hdr);
	printf("[HEADER] Size of mem : %d\n", hdr->blockNode.size);
	printf("[HEADER] Adress of mem : %x\n", hdr->blockNode.mem);
	printf("[HEADER] Next header adress : %x\n", hdr->blockNode.next);
	printf("\n");
# endif
}
