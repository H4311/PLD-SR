# include "ctx.h"
# include "gmem.h"

# include <stdlib.h> /* malloc */

ctx_s* __CTX_CURRENT_PROCESS_NAME;

ctx_s* create_ctx()
{
	ctx_s* pctx = (ctx_s*) malloc(sizeof(ctx_s));
	init_mem(pctx);
	return pctx;
}

void destroy_ctx(ctx_s* pctx)
{
	destroy_mem(pctx);
	free(pctx);
}
