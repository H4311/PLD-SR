#ifndef _GTHREADS_H_
#define _GTHREADS_H_

#include "commons.h"
#include "gContext.h"

#define STACK_SIZE 16384
#define NAME_SIZE 20

enum gState {INIT, RUNNING, END}; 

typedef void (gThread_func_t) (void*);

/**
 * GThread structure
 */
struct gThread
{  
    int id;
    char *name;
    enum gState state;
    void* stack;
    long esp;
    long ebp;
    gContext *context;
	gThread_func_t *func;
	void* args;
    struct gThread *nextThread;
};

typedef struct gThread gThread;

/**
 * List all threads in the task queue
 */
void listThreads();

/**
 * Start scheduler
 */
void startSched();

/**
 * System initialization
 */
void initSystem();

/**
 * Initialize Thread
 */
int initGThread(struct gThread *thread, char* threadName, int stackSize, gThread_func_t func, void *args);

/**
 * Create a new thread
 */
int createGThread(char *name, gThread_func_t thread, void* args, int stackSize);

/**
 * Start a GThread
 */
void startGThread();

/**
 * Thread switching
 */
void switchGThread(struct gThread *thread);

/**
 * Switch context
 */
void yield();

/**
 * Kill current thread
 */
void killCurrThread();

/**
 * Kill a thread
 */
int killGThread(int threadId);


/**
 * Enable/Disable interrupts
 */
void enableIT();
void disableIT();
 
  

#endif
