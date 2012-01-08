#include <setjmp.h>
#include <stdio.h>

static jmp_buf buf;

typedef struct {
	int esp; /* stack pointer */
	int ebp; /* base pointer */
	int returnValue; /* in case of throw */
	short mustReturnValue; /* boolean */
} ctx_s;

static ctx_s context;

typedef int (func_t)(int);

int try(ctx_s *pctx, func_t* f, int arg)
{
	int r;

	pctx->mustReturnValue = 0;
	asm ("movl %%ebp, %0" "\n\t" "movl %%esp, %1"
	: "=r"(pctx->ebp), "=r"(pctx->esp) /* output variables */
	: /* input variables */
	);
	
	if (pctx->mustReturnValue) {
		return pctx->returnValue;
	} else {
		return f(arg);
	}
}

int throw(ctx_s *pctx, int r)
{
	pctx->mustReturnValue = 1;
	pctx->returnValue = r;

	int bp = pctx->ebp;
	int sp = pctx->esp;

	/*printf("avant asm\n");*/
	asm ("movl %0, %%ebp" "\n\t" "movl %1, %%esp"
	:  /* output variables */
	: "r"(bp), "r"(sp)/* input variables */
	: "%ebp", "%esp"
	);
	printf("Ici\n");
	
	return 0;
}

int plusOne(int v)
{
	return ++v;
}

int main()
{
	int returnedValue = try(&context, plusOne, 1);
	printf("Valeur retournée : %d\n", returnedValue);
	
	if (returnedValue == 1337)
	{
		return 0;
	}

	throw(&context, 1337);
	
	return 0;
}
