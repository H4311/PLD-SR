#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
	long esp; /* stack pointer */
	long ebp; /* base pointer */

	short mustReturnValue; /* boolean */
	int returnValue;
} ctx_s;

ctx_s* context;
static int retValue;

typedef int (func_t)(int);

int doNothing()
{
	return 0;
}

void displayContext() 
{
	int bp, sp;
	asm ("movl %%ebp, %0" "\n\t" "movl %%esp, %1"
	: "=r"(bp), "=r"(sp) /* output variables */
	: /* input variables */
	);
	
	printf("ebp : %d, esp : %d \n", bp, sp);
}

int try(ctx_s *pctx, func_t* f, int arg)
{	
	pctx->mustReturnValue = 0;

	asm ("movl %%ebp, %0" "\n\t" "movl %%esp, %1"
	: "=r"(pctx->ebp), "=r"(pctx->esp) /* output variables */
	: /* input variables */
	);

	printf("ebp save : %d, esp save : %d\n", pctx->ebp, pctx->esp);

	if (pctx->mustReturnValue) {
		return 1337; /*pctx->returnValue;*/
	} else {
		return f(arg);
	}
	
}

int throw(ctx_s *pctx)
{
	pctx->mustReturnValue = 1;
	pctx->returnValue = retValue;

	long ebp = pctx->ebp;
	long esp = pctx->esp;

	asm ("movl %1, %%esp" "\n\t" "movl %0, %%ebp" "\n\t" /*"pop %%ebp" "\n\t" "ret"*/
	: /* output variables */
	: "r"(ebp), "r"(esp) /* input variables */
	: /*"%esp"/*, "%ebp" */
	);

}

static int mul(int depth)
{
	int i;

	switch (scanf("%d", &i)) {
		case EOF :
			return 1; /* neutral element */
		case 0 :
			printf("case 0");
			return mul(depth+1); /* erroneous read */
		case 1 :
			if (i)
			{
				return i * mul(depth+1);
			}
			else 
			{
				retValue = -1;
				throw(context);
				return 0;
			}
		default:
			return 0;
	}
	
}

int main()
{
	int product;
	context = (ctx_s*) malloc(sizeof(ctx_s));

	retValue = 0;
	printf("A list of int, please\n");
	product = try(context, (func_t*) mul, retValue);
	printf("product = %d\n", product);

	free(context);
	context = 0;
	return 0;
}
