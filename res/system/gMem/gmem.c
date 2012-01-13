# include "gmem.h"

# include <stdlib.h> /* malloc */

void* gmalloc(unsigned size)
{
	blockNode* current = __CTX_CURRENT_PROCESS_NAME->heap;
	
	/* useful to keep coherency */
	blockNode* previous = NULL; 
	
	/* the block which will be the next after the previous */
	blockNode* next = NULL; 
	
	/* the block of memory itself to return	*/
	void* blockToReturn = NULL; 
	
	/* First fit : looking for the first block which size is more than
	 * the one in arg */
	while (current != NULL)
	{
		if (current->size >= size)
		{
			break;
		} else {
			previous = current;
			current = current->next;
		}
	}
	
	/* if there's no current, then there's no free memory in da heap */
	if (current == NULL) 
	{
		return NULL;
	}
	
	/* Do we have to split the block or no ? */
	if (current->size > size)
	{
		blockNode* littleOne = (blockNode*) malloc(sizeof(blockNode));
		
		int currentSize = current->size;
		blockNode* currentNext = current->next;
		
		/* remove current block from memory ... */
		free(current->mem);
		free(current);
		
		/* ... by splitting it into a more little one and the returned 
		 * one */
		littleOne->size = currentSize - size;
		littleOne->next = currentNext;
		littleOne->mem = malloc(littleOne->size);
		
		/* the last manipulated block was the littleOne */
		next = littleOne;
		
		blockToReturn = malloc(size);
	} else {
		/* the next block will be the current's next block */
		next = current->next;
		blockToReturn = current->mem;
		
		free(current); /* removes block node, not memory ! */
	}
	
	/* Reajust the positions in the linked list */
	if (previous == NULL)
	{
		__CTX_CURRENT_PROCESS_NAME->heap = next;
	} else {
		previous->next = next;
	}
	
	return blockToReturn;
}

void gfree(void* ptr)
{
	blockNode* newBlock;

	if (ptr == NULL)
	{
		return;
	}
	
	/* TODO no fusion here ! */
	
	/* puts the new block in the list of empty blocks */
	newBlock = (blockNode*) malloc(sizeof(blockNode));
	newBlock->mem = ptr;
	newBlock->size = sizeof(*ptr);
	
	newBlock->next = __CTX_CURRENT_PROCESS_NAME->heap;
	__CTX_CURRENT_PROCESS_NAME->heap = newBlock;
}

void init_mem(ctx_s* pctx)
{
		pctx->heap = (blockNode*) malloc(sizeof(blockNode));
		
		pctx->heap->size = __GMEM_HEAP_SIZE;
		pctx->heap->next = NULL;
		pctx->heap->mem = malloc(__GMEM_HEAP_SIZE);
}

void destroy_mem(ctx_s* pctx)
{
		blockNode* current = pctx->heap;
		blockNode* next = NULL;
		
		while (current != NULL)
		{
			next = current->next;
			free(current->mem);
			free(current);
			current = next;
		}
}
