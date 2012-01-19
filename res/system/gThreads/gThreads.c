#include <stdlib.h>
#include <stdio.h>

#include "gThreads.h"

/**
 * Count id thread
 */
static int idCounter;

static gThread *firstThread;

/**
 * Initialize gThread system
 */
void initSystem() 
{
	/* TODO */
	
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
	newGThread->stack = malloc(stackSize);
	newGThread->nextThread = firstThread;
	firstThread = newGThread;
	
	printf("Création du GThread %s (n°%d)\n", newGThread->name, newGThread->id);
	return newGThread->id;
}


/**
 * Switch context
 */
void yield()
{
	
	
}


/**
 * Kill a thread with the id threadId
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

