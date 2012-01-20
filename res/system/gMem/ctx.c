# include "ctx.h"
# include "gmem.h"

# include <stdlib.h> /* malloc */

ctx_s* __CURRENT_CONTEXT;

ctx_s* create_ctx()
{
	return (ctx_s*) malloc(sizeof(ctx_s));
}

void destroy_ctx(ctx_s* pctx)
{
	free(pctx);
}
