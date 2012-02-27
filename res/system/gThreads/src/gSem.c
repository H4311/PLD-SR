#include <stdlib.h>

#include "gSem.h"


/* 
 * Semaphore must be created before a call to semInit
 */
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
