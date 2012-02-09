#include <stdlib.h>

#include "gSem.h"


/* Sémaphore déjà créé pour l'intialiser*/
void sem_init(semaphore *sem, unsigned int val)
{	
	sem->count = val;
	sem->threads = NULL;
}

/* semGive */
void sem_up(semaphore *sem)
{
	sem->count++;
	if (sem->count <=0)
	{
		if (sem->threads != NULL)
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
		if (sem->threads != NULL)
		{
			
			
		}
	}
}
