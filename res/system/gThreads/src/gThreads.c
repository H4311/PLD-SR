#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "gThreads.h"
#include "hw.h"

/**
 * Count id thread
 */
static int idCounter;

static gThread *firstThread;
static gThread *currThread;

/**
 * Initialisation du matériel
 */
void startSched()
{
	start_hw();
	setup_irq(4, yield);
	yield();
}

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
		thread->context = malloc(sizeof(gContext));
		(thread->context)->esp = (int)thread->stack+stackSize;
		(thread->context)->ebp = (int)thread->stack+stackSize;
		thread->func = func;
		thread->args = args;
		
		return OK;
	}
	else
	{
		return ERROR;
	}
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
			newGThread->nextThread = newGThread;
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
void switchGThread(gThread *thread)
{
	irq_disable();
	
    if (currThread)
    {
		asm("movl %%esp, %0" "\n" "movl %%ebp, %1"
            :"=r"(currThread->context->esp),
            "=r"(currThread->context->ebp) 
        );
	}
	
	/* Next context*/
    currThread = thread;
    
    asm("movl %0, %%esp" "\n" "movl %1, %%ebp"
        :
        :"r"(currThread->context->esp),
         "r"(currThread->context->ebp)
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
	gThread *thread = currThread;
	irq_disable();
		
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
		thread->nextThread = currThread->nextThread;
		free(currThread->stack);
		free(currThread);
		currThread = thread;
		printf("Switching to GThread n°%d\n", currThread->id);
		irq_enable();
		/* On continue l'ordo avec le prochain contexte */
		switchGThread(currThread);
	}
}

/**
 * Switch context
 */
void yield()
{
	if (currThread != NULL)
    {
        switchGThread(currThread->nextThread);
    }
    else
    {
        switchGThread(firstThread);
	}
	
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

