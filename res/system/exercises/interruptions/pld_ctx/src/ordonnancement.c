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
void idle(void *arg);

semaphore *sem;

struct rlimit limite;

void start_sched()
{
	start_hw();
	setup_irq(1, yield);
	yield();
}

void listContexts()
{
	int i;
	ctx_s *ctx;
	ctx = first_ctx;
	for (i=0;i<8;i++)
	{
		printf("%d", ctx->id);
		ctx = ctx->next_ctx;
	}
	puts("");
	
}

int main(int argc, char *argv[])
{
	/* Pour regarder les tailles de heap et stack dispo
	getrlimit(RLIMIT_STACK, &limite);
	printf("cur : %lu, max : %lu\n", limite.rlim_cur, limite.rlim_max);
	*/
	sem = malloc(sizeof(semaphore));
	
	id_counter = 0;
	curr_ctx = NULL;
	first_ctx = NULL;
	/*
	 * Création des différents contextes
	 */
	
	/*create_ctx(STACK_SIZE, idle, NULL);*/
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
		ctx->esp = (long)ctx->stack+stack_size;
		ctx->ebp = (long)ctx->stack+stack_size;
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
			curr_ctx = new_ctx;
			new_ctx->next_ctx = new_ctx; /* circulaire */
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
	switch_to_ctx(curr_ctx->next_ctx);
	
	/*
    if (curr_ctx != NULL)
    {
        switch_to_ctx(curr_ctx->next_ctx);
    }
    else
    {
        switch_to_ctx(first_ctx);
	}
	*/
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
	ctx_s *ctx;
	irq_disable();
	
	ctx = curr_ctx;
	
	/* Recherche du contexte précédent le contexte courant*/
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
		if (curr_ctx == first_ctx)
			first_ctx = ctx;
		ctx->next_ctx = curr_ctx->next_ctx;
		/*printf("Destruction context %d\n", curr_ctx->id);*/
		free(curr_ctx->stack);
		free(curr_ctx);
		curr_ctx = ctx;
		curr_ctx->state = RUNNING;
		printf("Passage au Thread n°%d\n", curr_ctx->id);
		
		/*
		asm("movl %0, %%esp" "\n" "movl %1, %%ebp"
        :
        :"r"(curr_ctx->esp),
         "r"(curr_ctx->ebp)
		);
		* */
		yield();
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
	for (;i<200;i++)
	{
		/*
		puts("A");
		puts("B");
		puts("C");
		*/
		printf("ctx %d (i=%d)\n", curr_ctx->id, i);
	}
}

void f_pong(void *args)
{
	int i = 0;
	for (;i<50;i++)
	{
		/*
		puts("1");
		puts("2");
		*/
		printf("ctx %d (i=%d)\n", curr_ctx->id, i);
	}
}

void f_paf(void *args)
{
	int i = 0;
	for (;i<10;i++)
	{
		/*
		puts("y");
		puts("z");
		*/
		printf("ctx %d (i=%d)\n", curr_ctx->id, i);
	}
}

void f_pif(void *args)
{
	int i = 0;
	for (;i<40;i++)
	{
		/*
		puts("p");
		puts("i");
		puts("f");
		*/
		printf("ctx %d (i=%d)\n", curr_ctx->id, i);
	}
}

void idle(void *args)
{
	while(1);
	
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
