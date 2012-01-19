#include <stdlib.h>
#include <stdio.h>

#include "gThreads.h"

/**
 * Count id thread
 */
static int idCounter;

static gThread *firstThread;
static gThread *currThread;

/**
 * Initialize gThread system
 */
void initSystem() 
{
	idCounter = 0;
	firstThread = NULL;
	currThread = NULL;
	
}

/**
 * Create a new thread
 */
int createGThread(char *threadName, gThread_func_t thread, void* args, int stackSize)
{
	gThread *newGThread= malloc(sizeof(gThread));
	if (idCounter == 0)
	{
		initSystem();
	}
	
	/* TODO : check stack size */
	newGThread->id = ++idCounter;
	newGThread->name = threadName;
	newGThread->launched = 0;
	newGThread->stack = malloc(stackSize);
	newGThread->nextThread = firstThread;
	firstThread = newGThread;
	currThread = firstThread;
	
	printf("Création du GThread %s (n°%d)\n", newGThread->name, newGThread->id);
	return newGThread->id;
}


/**
 * Switch context
 */
void yield()
{
	
	/* Saving stack pointers to the current context */
	asm ("movl %%ebp, %0" "\n\t" "movl %%esp, %1" "\n\t"
	: "=r"((currThread->context).ebp), "=r"((currThread->context).esp) /* output variables */
	: /* input variables */
	);
	
	if (currThread->nextThread == NULL)
	{
		currThread = firstThread;
	}
	else
	{
		currThread = currThread->nextThread;
	}
	
	if (!currThread->launched)
	{
		currThread->launched = 1;
		currThread->func(currThread->args);
	}
	
	/* Restore stack registers */
	asm ("movl %0, %%esp" "\n\t" "movl %1, %%ebp" "\n\t"
	:  /* output variables */
	: "r"((currThread->context).esp), "r"((currThread->context).ebp) /* input variables */
	: /*"%esp", "%ebp" */
	);	
	
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
	printf("Destruction du GThread %s (n°%d)\n", itThread->name, itThread->id);
	free(itThread->stack);
	free(itThread);
	return OK;
}

