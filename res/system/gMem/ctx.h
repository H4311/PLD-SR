# ifndef __CTX_H__
# define __CTX_H__

# define HEAP_SIZE 1024

typedef struct {
	void* heap;
} ctx_s;

ctx_s* create_ctx();
void destroy_ctx(ctx_s* pctx);

extern ctx_s* context;

# endif
