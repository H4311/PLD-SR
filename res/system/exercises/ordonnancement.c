#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define STACK_SIZE 16384

typedef void (func_t) (void*);

struct ctx_s {
	int id;
	int launched;
	long esp; /* stack pointer */
	long ebp; /* base pointer */
	void* stack;
	func_t *f;
	void* args;
	struct ctx_s *next_ctx;
};

typedef struct ctx_s ctx_s;

static int id_counter;
static ctx_s *curr_ctx;
static ctx_s *first_ctx;

int create_ctx(int stack_size, func_t f, void *args);
void f_ping(void *arg);
void f_pong(void *arg);
void yield();
void destroy_all_ctx();

int main(int argc, char *argv[])
{
	id_counter = 1;
	create_ctx(STACK_SIZE, f_ping, NULL);
	create_ctx(STACK_SIZE, f_pong, NULL);
	curr_ctx = first_ctx;
	yield();
	destroy_all_ctx();
	exit(EXIT_SUCCESS);
}

int create_ctx(int stack_size, func_t f, void *args)
{
	static ctx_s* temp_ctx = NULL;
	/* First context */
	curr_ctx = (ctx_s*) malloc(sizeof(ctx_s));
	curr_ctx->id = id_counter;
	curr_ctx->launched = 0;
	curr_ctx->stack = malloc(stack_size);
	curr_ctx->f = f;
	curr_ctx->args = args;
	curr_ctx->next_ctx = NULL;
	
	if (id_counter == 1)
	{
		first_ctx = curr_ctx;
	}
	
	id_counter++;
	//printf("Contexte %d créé\n", curr_ctx->id);
	
	if (temp_ctx != NULL)
	{
		temp_ctx->next_ctx = curr_ctx;
	}
	temp_ctx = curr_ctx;
	curr_ctx = curr_ctx->next_ctx;
	
}

void yield() 
{
	
	/* Saving stack pointers to the current context */
	asm ("movl %%ebp, %0" "\n\t" "movl %%esp, %1"
	: "=r"(curr_ctx->ebp), "=r"(curr_ctx->esp) /* output variables */
	: /* input variables */
	);
		
	if (curr_ctx->next_ctx == NULL)
	{
		curr_ctx = first_ctx;
	}
	else
	{
		curr_ctx = curr_ctx->next_ctx;
	}
	
	if (!curr_ctx->launched)
	{
		curr_ctx->launched = 1;
		curr_ctx->f(curr_ctx->args);
	}
	
	/* Restore stack registers */
	asm ("movl %0, %%esp" "\n\t" "movl %1, %%ebp"
	:  /* output variables */
	: "r"(curr_ctx->esp), "r"(curr_ctx->ebp) /* input variables */
	: /*"%esp"/*, "%ebp" */
	);	
	
}

void destroy_all_ctx()
{
	ctx_s *temp_ctx;
	curr_ctx = first_ctx;
	while (curr_ctx != NULL)
	{
		//printf("Contexte %d à détruire\n", curr_ctx->id);
		temp_ctx = curr_ctx->next_ctx ;
		if (temp_ctx != NULL)
			printf("Prochaine Contexte à détruire : %d\n", temp_ctx->id);
		//printf("Destruction du contexte %d ... ", curr_ctx->id);
		free(curr_ctx);
		//printf("... réussie !\n");
		curr_ctx = temp_ctx;
	} 
	
}

void f_ping(void *args)
{
	while(1) 
	{
		printf("A") ;
		yield();
		printf("B") ;
		yield();
		printf("C") ;
		yield();
	}
}

void f_pong(void *args)
{
	while(1) 
	{
		printf("1") ;
		yield();
		printf("2") ;
		yield();
	}

}
