# ifndef __CTX_H__
# define __CTX_H__

# define __CURRENT_CONTEXT context
# define __HEAP_SIZE 512

/*****************************************************
 * The structure modeling an execution context
 **/
typedef struct {
	char heap[__HEAP_SIZE];
} ctx_s;

/*****************************************************
 * The context which has been chosen by the scheduler 
 **/
extern ctx_s* __CURRENT_CONTEXT;

/*****************************************************
 * Function to create an execution context
 **/
ctx_s* create_ctx();

/*****************************************************
 * Function to destroy an execution context
 **/
void destroy_ctx(ctx_s* pctx);

# endif
