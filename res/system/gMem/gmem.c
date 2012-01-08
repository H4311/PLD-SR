# include "gmem.h"
# include "ctx.h"

typedef struct
{
	void* mem;
	struct blockNode* next;
} blockNode;

static blockNode* freeBlocksList;

void* gmalloc(unsigned size)
{
	
}

void gfree(void* ptr)
{
	
}

void init_mem(ctx_s* pctx)
{
		pctx->heap = malloc(HEAP_SIZE);
}
