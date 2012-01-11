#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
	long esp; /* stack pointer */
	long ebp; /* base pointer */
	
	short mustReturnValue; /* boolean */
} ctx_s;

ctx_s* context;
static int returnValue;

typedef int (func_t)(int);

int try(ctx_s *pctx, func_t* f, int arg)
{	
	pctx->mustReturnValue = 0;
	
	asm ("movl %%ebp, %0" "\n\t" "movl %%esp, %1"
	: "=r"(pctx->ebp), "=r"(pctx->esp) /* output variables */
	: /* input variables */
	);
	
	if (pctx->mustReturnValue) {
		return returnValue;
	} else {
		return f(arg);
	}
}

int throw(ctx_s *pctx, int r)
{
	pctx->mustReturnValue = 1;
	returnValue = r;

	long ebp = pctx->ebp;
	long esp = pctx->esp;

	asm ("movl %1, %%esp" "\n\t" "movl %0, %%ebp"
	:  /* output variables */
	: "r"(ebp), "r"(esp) /* input variables */
	: "%esp"/*, "%ebp" */
	);
}

static int mul(int depth)
{
	int i;
	
	switch (scanf("%d", &i)) {
		case EOF :
			return 1; /* neutral element */
		case 0 :
			return mul(depth+1); /* erroneous read */
		case 1 :
			if (i)
				return i * mul(depth+1);
			else
				throw(context, -1);
				return 0;
		default:
			return 0;
	}
}

int main()
{
	int product = 0;
	context = (ctx_s*) malloc(sizeof(ctx_s));
	
	printf("A list of int, please\n");
	product = try(context, (func_t*) mul, 0);
	printf("product = %d\n", product);
	
	free(context);
	context = 0;
	return 0;
}
