#include <stdlib.h>

#include "gSem.h"


/* Sémaphore déjà créé pour l'intialiser*/
void semInit(semaphore *sem, unsigned int val)
{	
	sem->count = val;
	sem->threads = NULL;
}

/* semGive */
void semGive(semaphore *sem)
{
	sem->count++;
}

/* semTake (wait) */
void semTake(semaphore *sem)
{
	sem->count--;
	while(sem->count < 0);
}
