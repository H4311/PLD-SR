#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/resource.h>

#include "hw.h"

#define STACK_SIZE 16384

enum ctx_state {INIT, RUNNING, END}; 

typedef void (func_t) (void*);

/*
 * Contexte
 */
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

/*
 * Sémaphore
 */
struct semaphore {
	int count;
	struct ctx_s *ctx; /* Liste des contextes en attente */
};
typedef struct semaphore semaphore;

static int id_counter;
static int runningContexts;

static ctx_s *curr_ctx;
/* 
 * first_ctx peut ne pas etre utile, 
 * la chaine des contextes étant circulaire 
 */
static ctx_s *first_ctx;

void start_sched();

int create_ctx(int stack_size, func_t f, void *args);
int init_ctx(struct ctx_s *ctx, int stack_size, func_t f, void *args); 

void display_ctx();
void switch_to_ctx(struct ctx_s *ctx); 
void start_ctx();
void yield(void);
void kill_context();
void destroy_all_ctx();

void sem_init(semaphore *sem, unsigned int val);
void sem_up(semaphore *sem);
void sem_down(semaphore *sem);

void f_ping(void *arg);
void f_pong(void *arg);
void f_paf(void *arg);
void f_pif(void *arg);

semaphore *sem;

struct rlimit limite;

void start_sched()
{
	start_hw();
	setup_irq(4, yield);
	yield();
}

int main(int argc, char *argv[])
{
	/* Pour regarder les tailles de heap et stack dispo
	getrlimit(RLIMIT_STACK, &limite);
	printf("cur : %lu, max : %lu\n", limite.rlim_cur, limite.rlim_max);
	*/
	sem = malloc(sizeof(semaphore));
	
	id_counter = 0;
	runningContexts = 0;
	curr_ctx = NULL;
	first_ctx = NULL;
	/*
	 * Création des différents contextes
	 */
	create_ctx(STACK_SIZE, f_ping, NULL);
	create_ctx(STACK_SIZE, f_pong, NULL);
	create_ctx(STACK_SIZE, f_paf, NULL);
	create_ctx(STACK_SIZE, f_pif, NULL);

	sem_init(sem, 4);
	
	/*
	 * Initialisation de l'ordo
	 */ 
	start_sched();
	
	printf("Destruction des contextes\n");
	/*destroy_all_ctx();*/
	exit(EXIT_SUCCESS);
}


int init_ctx(struct ctx_s *ctx, int stack_size, func_t f, void *args)
{
    ctx->stack = malloc(stack_size);
    if (ctx->stack)
    {
		ctx->id = ++id_counter;
		ctx->state = INIT;
		ctx->esp = (int)ctx->stack+stack_size;
		ctx->ebp = (int)ctx->stack+stack_size;
		ctx->f = f;
		ctx->args = args;
		return 0;
	}
	else
	{
		printf("Erreur initialisation du contexte\n");
		return -1;
	}
}

int create_ctx(int stack_size, func_t f, void *args)
{
	ctx_s *new_ctx = (ctx_s *)malloc(sizeof(ctx_s));
	if (!new_ctx)
	{
		printf("Erreur création du contexte\n");
		return -1;
	}
	else
	{
		/* Initialisation */
		init_ctx(new_ctx, stack_size, f, args);
		if (id_counter == 1) 
		{
			/* 1er contexte */
			first_ctx = new_ctx;
			new_ctx->next_ctx = first_ctx; /* circulaire */
		}
		else 
		{
			/* Insertion en tête après first_ctx */
			new_ctx->next_ctx = first_ctx->next_ctx;
			first_ctx->next_ctx = new_ctx;
		}    
		
	}
	return 0;
	
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
    /* Quand le thread se termine (tout seul), on revient ici */
    curr_ctx->state = END;
    /* Kill current thread */
    kill_context();
}

/* Kill le contexte courant */
void kill_context()
{
	ctx_s *ctx = curr_ctx;
	irq_disable();
		
	/* Recherche du context précédent le contexte courant*/
	while (ctx->next_ctx != curr_ctx)
	{
		ctx = ctx->next_ctx;
	}

	/* Un seul contexte restant */
	if (ctx == curr_ctx)
	{
		free(curr_ctx->stack);
		free(curr_ctx);
		/* 
		 * On quitte l'appli
		 * TODO : a revoir
		 * Faire une restitution du contexte initial ?
		 */
		free(sem);
		exit(EXIT_SUCCESS);
	}
	else
	{
		ctx->next_ctx = curr_ctx->next_ctx;
		free(curr_ctx->stack);
		free(curr_ctx);
		curr_ctx = ctx;
		printf("Passage au Thread n°%d\n", curr_ctx->id);
		irq_enable();
		/* On continue l'ordo avec le prochain contexte */
		switch_to_ctx(curr_ctx);
	}
}


/* Sémaphore déjà créé pour l'intialiser*/
void sem_init(semaphore *sem, unsigned int val)
{	
	sem->count = val;
	sem->ctx = NULL;
}

/* semGive */
void sem_up(semaphore *sem)
{
	sem->count++;
	if (sem->count <=0)
	{
		if (sem->ctx != NULL)
		{
	
		}
	}
	
}

/* semTake (wait) */
void sem_down(semaphore *sem)
{
	sem->count--;
	if (sem->count <=0)
	{
		if (sem->ctx != NULL)
		{
			
			
		}
	}
}


void f_ping(void *args)
{
	int i = 0;
	for (;i<20;i++)
	{
		/*
		puts("A");
		puts("B");
		puts("C");
		*/
		printf("ping %d (ctx %d)\n", i, curr_ctx->id);
	}
}

void f_pong(void *args)
{
	int i = 0;
	for (;i<30;i++)
	{
		/*
		puts("1");
		puts("2");
		*/
		printf("pong %d (ctx %d)\n", i, curr_ctx->id);
	}
}

void f_paf(void *args)
{
	int i = 0;
	for (;i<3;i++)
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
	for (;i<5;i++)
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
		temp_ctx = curr_ctx->next_ctx ;
		if (temp_ctx != NULL)
			printf("Prochain Contexte à détruire : %d\n", temp_ctx->id);
		free(curr_ctx);
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
