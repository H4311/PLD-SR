#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/resource.h>

#define STACK_SIZE 16384

enum ctx_state {INIT, RUNNING, END}; 

typedef void (func_t) (void*);

struct ctx_s {
	int id;
	enum ctx_state state;
	long esp; 
	long ebp; 
	void* stack;
	func_t *f;
	void* args;
	struct ctx_s *next_ctx;
};

typedef struct ctx_s ctx_s;

static int id_counter;

static ctx_s *curr_ctx;
static ctx_s *first_ctx;

void start_sched();

int create_ctx(int stack_size, func_t f, void *args);
int init_ctx(struct ctx_s *ctx, int stack_size, func_t f, void *args); 

void display_ctx();
void switch_to_ctx(struct ctx_s *ctx); 
void start_ctx();
void yield(void);
void destroy_all_ctx();

void f_ping(void *arg);
void f_pong(void *arg);
void f_paf(void *arg);
void f_pif(void *arg);

struct rlimit limite;

void start_sched()
{
	start_hw();
	setup_irq(4, yield);
	
}

int main(int argc, char *argv[])
{
	/* Pour regarder les tailles de heap et stack dispo
	getrlimit(RLIMIT_STACK, &limite);
	printf("cur : %lu, max : %lu\n", limite.rlim_cur, limite.rlim_max);
	*/
	
	id_counter = 0;
	curr_ctx = NULL;
	first_ctx = NULL;
	/*
	 * Création des différents contextes
	 */
	create_ctx(STACK_SIZE, f_ping, NULL);
	create_ctx(STACK_SIZE, f_pong, NULL);
	create_ctx(STACK_SIZE, f_paf, NULL);
	create_ctx(STACK_SIZE, f_pif, NULL);

	/*
	 * Initialisation de l'ordo
	 */ 
	start_sched();

	destroy_all_ctx();
	exit(EXIT_SUCCESS);
}


int init_ctx(struct ctx_s *ctx, int stack_size, func_t f, void *args)
{
    ctx->stack = malloc(stack_size);
    if (ctx->stack)
    {
		ctx->id = ++id_counter;
		ctx->state = INIT;
		ctx->esp = ctx->stack+stack_size;
		ctx->ebp = ctx->stack+stack_size;
		ctx->f = f;
		ctx->args = args;
	}
}

int create_ctx(int stack_size, func_t f, void *args)
{
	ctx_s *new_ctx = (ctx_s *)malloc(sizeof(ctx_s));
	if (!new_ctx)
	{
		printf("Erreur création du contexte\n");
		return 0;
	}
	else
	{
		/* Initialisation */
		init_ctx(new_ctx, stack_size, f, args);
		if (id_counter == 1) 
		{
			/* 1er contexte */
			first_ctx = new_ctx;
			new_ctx->next_ctx = new_ctx; /* circulaire */
		}
		else 
		{
			/* Insertion en tête */
			new_ctx->next_ctx = first_ctx->next_ctx;
			first_ctx->next_ctx = new_ctx;
		}    
		
	}
	
}

void switch_to_ctx(struct ctx_s *ctx)
{
	irq_disable();
    assert(ctx->state != END);
    if (curr_ctx)
    {
        asm("movl %%esp, %0" "\n" "movl %%ebp, %1"
            :"=r"(curr_ctx->esp),
            "=r"(curr_ctx->ebp) 
        );
	}
	
	/* Contexte suivant */
    curr_ctx=ctx;
    
    asm("movl %0, %%esp" "\n" "movl %1, %%ebp"
        :
        :"r"(curr_ctx->esp),
         "r"(curr_ctx->ebp)
    );
    
    irq_enable();
    
    if (curr_ctx->state == INIT)
    {
        start_ctx();
    }
    
} 

void yield(void) 
{
    if (curr_ctx != NULL)
    {
        switch_to_ctx(curr_ctx->next_ctx);
    }
    else
    {
        switch_to_ctx(first_ctx);
	}
}


void start_ctx()
{
    curr_ctx->state = RUNNING;
    curr_ctx->f(curr_ctx->args);  
    curr_ctx->state = END;
    free(curr_ctx->stack);
    exit(EXIT_SUCCESS);
}

void f_ping(void *args)
{
	int i = 0;
	for (;;)
	{
		/*
		puts("A");
		puts("B");
		puts("C");
		*/
		puts("ping");
	}
}

void f_pong(void *args)
{
	int i = 0;
	for (;;)
	{
		/*
		puts("1");
		puts("2");
		*/
		puts("pong");
	}
}

void f_paf(void *args)
{
	int i = 0;
	for (;;)
	{
		/*
		puts("y");
		puts("z");
		*/
		puts("paf");
	}
}

void f_pif(void *args)
{
	int i = 0;
	for (;;)
	{
		/*
		puts("p");
		puts("i");
		puts("f");
		*/
		puts("pif");
	}
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
			printf("Prochain Contexte à détruire : %d\n", temp_ctx->id);
		//printf("Destruction du contexte %d ... ", curr_ctx->id);
		free(curr_ctx);
		//printf("... réussie !\n");
		curr_ctx = temp_ctx;
	} 
	
}

void display_ctx()
{
	curr_ctx = first_ctx;
	while (curr_ctx != NULL)
	{
		printf("Id : %d; ", curr_ctx->id);
		curr_ctx = curr_ctx->next_ctx;
	}
	printf("\n");
	
}
