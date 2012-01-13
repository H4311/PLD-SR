#include <setjmp.h>
#include <stdio.h>


typedef struct {
	int esp; /* stack pointer */
	int ebp; /* base pointer */
	void* stack[];
	
	/*todo*/
	
} ctx_s;

struct ctx_s ctx_ping;
struct ctx_s ctx_pong;


void f_ping(void *arg);
void f_pong(void *arg);


void init_ctx(ctx_s *ctx, int stack_size, func_t f, void *args)
{
	asm ("movl %%ebp, %0" "\n\t" "movl %%esp, %1"
	: "=r"(ctx->ebp), "=r"(ctx->esp) /* output variables */
	: /* input variables */
	);
		
	/*TODO*/
	
}


void switch_to_ctx(ctx_s *ctx)
{
	/*todo*/
	
	
}


int main(int argc, char *argv[])
{
	init_ctx(&ctx_ping, 16384, f_ping, NULL);
	init_ctx(&ctx_pong, 16384, f_pong, NULL);
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
