# ifndef __GMEM_INTERFACE_H__
# define __GMEM_INTERFACE_H__

# define __CTX_CURRENT_PROCESS_NAME context

# define __GMEM_HEAP_TYPE blockNode*
# define __GMEM_HEAP_SIZE 1024

typedef struct
{
	unsigned size;
	void* mem;
	struct blockNode* next;
} blockNode;

typedef struct {
	char heap[__GMEM_HEAP_SIZE];
} ctx_s;

extern ctx_s* __CTX_CURRENT_PROCESS_NAME;

# endif
