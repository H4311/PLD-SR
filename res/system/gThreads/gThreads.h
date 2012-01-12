#ifndef _GTHREADS_H_
#define _GTHREADS_H_

#define STACK_SIZE 1042
#define NAME_SIZE 20


typedef struct {
	int esp; /* stack pointer */
	int ebp; /* base pointer */

	/* todo */
	
} ctx_s;


typedef struct gThread
{  
    int id;
    char name[NAME_SIZE];
    int priority;
    int stackSize;
	ctx_s context;
    
} gThread;



/**
 * Initialisation du système
 */
void init();

/**
 * création d'un nouveau thread
 */
void createThread();

/**
 * Changement de contexte
 */
void yield();


#endif
