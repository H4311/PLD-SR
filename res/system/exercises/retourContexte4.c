#include <setjmp.h>
#include <stdio.h>

static jmp_buf buf;

typedef struct {
	int esp; /* stack pointer */
	int ebp; /* base pointer */
	int returnValue; /* in case of throw */
	short mustReturnValue; /* boolean */
} ctx_s;


typedef int (func_t)(int);


int displayContext()
{
	int bp, sp;
	
	asm ("movl %%ebp, %0" "\n\t" "movl %%esp, %1"
	: "=r"(bp), "=r"(sp) /* output variables */
	: /* input variables */
	);

	printf("Valeur de bp : %d\nValeur de sp : %d\n", bp, sp);
	
}

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
	asm ("movl %0, %%esp" "\n\t" "movl %1, %%ebp"
	: /* output variables */
	: "r"(sp), "r"(bp)/* input variables */
	:
	);
	
	return 0;
}

int plusOne(int v)
{
	return ++v;
}


int main()
{
	ctx_s context;
	printf("Avant le try: ");
	displayContext(&context);
	int returnedValue = try(&context, plusOne, 1);
	displayContext();

	printf("Valeur retournée : %d\n", returnedValue);
	
	if (returnedValue == 1337)
	{
		printf("Si 1337 : ");
		displayContext();
		return 0;
	}

	printf("Avant le throw : ");
	displayContext();
	throw(&context, 1337);
	printf("Apres le throw : "); 
	displayContext();
	
	return 0;
}
