#ifndef _GSEM_H_
#define _GSEM_H_

#include "gThreads.h"

/*
 * Sémaphore
 */
struct semaphore {
	int count;
	struct gThread *threads; /* Waiting threads list */
};
typedef struct semaphore semaphore;


void semInit(semaphore *sem, unsigned int val);
void semGive(semaphore *sem);
void semTake(semaphore *sem);


#endif
