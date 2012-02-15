#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "commons.h"
#include "gThreads.h"
#include "gSem.h"
#include "hw.h"

/**
 * Count id thread
 */
static int idCounter = 0;

static gThread *firstThread = NULL;
static gThread *currThread = NULL;

/**
 * Initialize hardware
 */
void startSched()
{
	start_hw();
	setup_irq(4, yield);
	yield();
}

/**
 * List all threads currently in the task queue
 */
void listThreads()
{
	int i;
	gThread *thread;
	thread = firstThread;
	for (i=0; i<8; i++)
	{
		printf("%d", thread->id);
		thread = thread->nextThread;
	}
	puts("");
}


/**
 * Initialize Thread
 */
int initGThread(struct gThread *thread, char* threadName, int stackSize, gThread_func_t func, void *args)
{
    thread->stack = malloc(stackSize);
    if (thread->stack)
    {
		thread->id = ++idCounter;
		thread->name = threadName;
		thread->state = INIT;
		thread->esp = (long)thread->stack+stackSize;
		thread->ebp = (long)thread->stack+stackSize;
		thread->func = func;
		thread->args = args;
		
		return OK;
	}
	else
	{
		printf("Error initializing gThread\n");
		return ERROR;
	}
}


/**
 * Create a new thread
 */
int createGThread(char *threadName, gThread_func_t thread, void* args, int stackSize)
{
	gThread *newGThread= malloc(sizeof(gThread));
	
	if (!newGThread)
	{
		printf("Error creating gThread\n");
		return 0;
	}
	else
	{
		/*Initialize thread*/
		initGThread(newGThread, threadName, stackSize, thread, args);
		if (idCounter == 1) 
		{
			/* 1st thread */
			firstThread = newGThread;
			currThread = firstThread;
			newGThread->nextThread = newGThread; /* Ring buffer */
		}
		else 
		{
			/* top insertion */
			newGThread->nextThread = firstThread->nextThread;
			firstThread->nextThread = newGThread;
		}  
	}
	printf("GThread created \"%s\" (n°%d)\n", newGThread->name, newGThread->id);
	return newGThread->id;
}


/**
 * Thread switching
 */
void switchGThread(struct gThread *thread)
{
	irq_disable();
	
    if (currThread)
    {
		asm("movl %%esp, %0" "\n" "movl %%ebp, %1"
            :"=r"(currThread->esp),
            "=r"(currThread->ebp) 
        );
	}
	
	/* Next context*/
	currThread = thread;
	
	asm("movl %0, %%esp" "\n" "movl %1, %%ebp"
		:
		:"r"(currThread->esp),
		 "r"(currThread->ebp)
	);
   
    irq_enable();
    
    if (currThread->state == INIT)
    {
        startGThread();
    }
    
} 

/**
 * Start GThread
 */
void startGThread()
{
    currThread->state = RUNNING;
    currThread->func(currThread->args);  
    /* Thread stopped its routine*/
    currThread->state = END;
    /* Kill current Thread */
    killCurrThread();
}

/** 
 * Kill current context 
 */
void killCurrThread()
{
	gThread *thread;
	irq_disable();
	
	thread = currThread;
		
	/* Recherche du context précédent le contexte courant*/
	while (thread->nextThread != currThread)
	{
		thread = thread->nextThread;
	}

	/* Un seul contexte restant */
	if (thread == currThread)
	{
		free(currThread->stack);
		free(currThread);
		/* 
		 * On quitte l'appli
		 * TODO : a revoir
		 * Faire une restitution du contexte initial ?
		 */
		/*free(sem);*/
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (currThread == firstThread)
			firstThread = thread;
		thread->nextThread = currThread->nextThread;
		free(currThread->stack);
		free(currThread);
		currThread = thread;
		currThread->state = RUNNING;
		yield();
	
	}
}

/**
 * Switch context
 */
void yield()
{
	irq_disable();
	switchGThread(currThread->nextThread);
}


/**
 * Kill a thread with the id "threadId"
 */
int killGThread(int threadId)
{
	gThread* itThread;
	itThread = firstThread;
	
	while (itThread->id != threadId)
	{
		itThread = itThread->nextThread;
		if (itThread == NULL)
			return ERROR;
	}
	printf("GThread \"%s\" (n°%d) killed\n", itThread->name, itThread->id);
	/*free(itThread->stack);*/
	free(itThread);
	return OK;
}

