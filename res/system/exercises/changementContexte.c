#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define STACK_SIZE 16384

typedef void (func_t) (void*);

typedef struct {
	int id;
	int launched;
	long esp; /* stack pointer */
	long ebp; /* base pointer */
	void* stack;
	func_t *f;
	void* args;
} ctx_s;

static ctx_s *curr_ctx;
ctx_s ctx_ping;
ctx_s ctx_pong;

int init_ctx(ctx_s *ctx, int stack_size, func_t f, void *args);
void f_ping(void *arg);
void f_pong(void *arg);
void switch_to_ctx(ctx_s *ctx);

int main(int argc, char *argv[])
{
	ctx_ping.id = 1;
	ctx_pong.id = 2;
	ctx_ping.launched = 0;
	ctx_pong.launched = 0;
	init_ctx(&ctx_ping, STACK_SIZE, f_ping, NULL);
	init_ctx(&ctx_pong, STACK_SIZE, f_pong, NULL);
	curr_ctx = &ctx_ping;
	switch_to_ctx(&ctx_ping);
	exit(EXIT_SUCCESS);
}

void f_ping(void *args)
{
	while(1) 
	{
		printf("A") ;
		switch_to_ctx(&ctx_pong);
		printf("B") ;
		switch_to_ctx(&ctx_pong);
		printf("C") ;
		switch_to_ctx(&ctx_pong);
	}
}

void f_pong(void *args)
{
	while(1) 
	{
		printf("1") ;
		switch_to_ctx(&ctx_ping);
		printf("2") ;
		switch_to_ctx(&ctx_ping);
	}

}

int init_ctx(ctx_s *ctx, int stack_size, func_t f, void *args)
{
	ctx->stack = malloc(stack_size);
	ctx->f = f;
	ctx->args = args;
	printf("Contexte %d initialisé\n", ctx->id);
}


void switch_to_ctx(ctx_s *ctx)
{
	//printf("Saving context %d ... \n", curr_ctx->id);
	/* Saving stack pointers to the current context */
	asm ("movl %%ebp, %0" "\n\t" "movl %%esp, %1"
	: "=r"(curr_ctx->ebp), "=r"(curr_ctx->esp) /* output variables */
	: /* input variables */
	);
	
	/* Defines the new context */
	curr_ctx = ctx;
	
	if (!ctx->launched)
	{
		ctx->launched = 1;
		ctx->f(ctx->args);
	}
	
	//printf("Switching to context %d ... \n", curr_ctx->id);
	/* Restore stack registers */
	asm ("movl %0, %%esp" "\n\t" "movl %1, %%ebp"
	:  /* output variables */
	: "r"(curr_ctx->esp), "r"(curr_ctx->ebp) /* input variables */
	: /*"%esp"/*, "%ebp" */
	);	
	
	//printf("Switched to context %d ... \n", curr_ctx->id);
	
}
