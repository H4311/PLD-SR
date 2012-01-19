#ifndef _GTHREADS_H_
#define _GTHREADS_H_

#define FALSE 0
#define TRUE 1

#define ERROR -1
#define OK 0

#define STACK_SIZE 1042
#define NAME_SIZE 20

typedef void (gThread_func_t) (void*);

typedef struct {
	int esp; /* stack pointer */
	int ebp; /* base pointer */
	
} ctx_s;

typedef struct gThread
{  
    int id;
    char *name;
    int priority;
    int stackSize;
    void* stack;
    ctx_s context;
	gThread_func_t *func;
	void* args;
    struct gThread *nextThread;
} gThread;


/**
 * System initialization
 */
void initSystem();

/**
 * Create a new thread
 */
int createGThread(char *name, gThread_func_t thread, void* args, int stackSize);

/**
 * Kill a thread
 */
int killGThread(int threadId);

/**
 * Switch context
 */
void yield();


/**
 * Enable/Disable interrupts
 */
void enableIT();
void disableIT();
 
  

#endif
